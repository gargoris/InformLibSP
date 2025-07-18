# Automated PDF conversion script for all MD files
Write-Host "=== AUTOMATED MD TO PDF CONVERTER ===" -ForegroundColor Green

# Check VS Code availability
try {
    $null = Get-Command code -ErrorAction Stop
    Write-Host "VS Code found and available" -ForegroundColor Green
} catch {
    Write-Host "ERROR: VS Code not found in PATH!" -ForegroundColor Red
    exit 1
}

# Navigate to docs directory if needed
if (-not (Get-Location).Path.EndsWith("docs")) {
    if (Test-Path "docs") {
        Set-Location "docs"
        Write-Host "Moved to docs directory" -ForegroundColor Yellow
    } else {
        Write-Host "ERROR: docs directory not found!" -ForegroundColor Red
        exit 1
    }
}

# Get all MD files
$mdFiles = Get-ChildItem -Filter "*.md" | Sort-Object Name
Write-Host "Found $($mdFiles.Count) Markdown files to convert" -ForegroundColor Cyan

if ($mdFiles.Count -eq 0) {
    Write-Host "No Markdown files found!" -ForegroundColor Red
    exit 1
}

# Create batch conversion script for VS Code
$batchScript = @"
const vscode = require('vscode');

async function convertAllMarkdownToPDF() {
    console.log('Starting batch PDF conversion...');
    
    const workspaceFolder = vscode.workspace.workspaceFolders[0];
    if (!workspaceFolder) {
        vscode.window.showErrorMessage('No workspace folder found');
        return;
    }
    
    const files = await vscode.workspace.findFiles('**/*.md', null, 100);
    console.log(`Found ${files.length} markdown files`);
    
    for (const file of files) {
        try {
            console.log(`Converting: ${file.fsPath}`);
            const document = await vscode.workspace.openTextDocument(file);
            await vscode.window.showTextDocument(document);
            
            // Wait a moment for the document to load
            await new Promise(resolve => setTimeout(resolve, 500));
            
            // Execute the markdown-pdf export command
            await vscode.commands.executeCommand('markdown-pdf.pdf');
            
            // Wait for conversion to complete
            await new Promise(resolve => setTimeout(resolve, 2000));
            
            console.log(`Converted: ${file.fsPath}`);
        } catch (error) {
            console.error(`Error converting ${file.fsPath}:`, error);
        }
    }
    
    vscode.window.showInformationMessage('Batch PDF conversion completed!');
}

// Execute the function
convertAllMarkdownToPDF();
"@

# Save the batch script
$batchScript | Out-File -FilePath "batch_convert.js" -Encoding UTF8

Write-Host "`nCreated batch conversion script: batch_convert.js" -ForegroundColor Green

# Alternative method: Use PowerShell to open each file and trigger conversion
Write-Host "`nStarting automated conversion process..." -ForegroundColor Yellow

$convertedCount = 0
$errorCount = 0

foreach ($file in $mdFiles) {
    Write-Host "Converting: $($file.Name)" -ForegroundColor White
    
    try {
        # Open the file in VS Code
        Start-Process -FilePath "code" -ArgumentList $file.FullName -Wait -WindowStyle Hidden
        
        # Wait for file to load
        Start-Sleep -Seconds 2
        
        # Try to trigger PDF conversion using command line
        $convertCommand = "code --command markdown-pdf.pdf $($file.FullName)"
        Invoke-Expression $convertCommand
        
        # Wait for conversion
        Start-Sleep -Seconds 3
        
        # Check if PDF was created
        $pdfFile = $file.FullName -replace '\.md$', '.pdf'
        if (Test-Path $pdfFile) {
            Write-Host "  ✅ Success: $($file.Name) -> $([System.IO.Path]::GetFileNameWithoutExtension($file.Name)).pdf" -ForegroundColor Green
            $convertedCount++
        } else {
            Write-Host "  ❌ Failed: PDF not found for $($file.Name)" -ForegroundColor Red
            $errorCount++
        }
        
    } catch {
        Write-Host "  ❌ Error converting $($file.Name): $($_.Exception.Message)" -ForegroundColor Red
        $errorCount++
    }
}

Write-Host "`n=== CONVERSION SUMMARY ===" -ForegroundColor Cyan
Write-Host "Total files: $($mdFiles.Count)" -ForegroundColor White
Write-Host "Converted: $convertedCount" -ForegroundColor Green
Write-Host "Errors: $errorCount" -ForegroundColor Red

if ($convertedCount -gt 0) {
    Write-Host "`n✅ Conversion completed! Check the docs directory for PDF files." -ForegroundColor Green
} else {
    Write-Host "`n❌ No files were converted. Trying manual method..." -ForegroundColor Yellow
    
    Write-Host "`nMANUAL CONVERSION INSTRUCTIONS:" -ForegroundColor Cyan
    Write-Host "1. Open VS Code in this directory: code ." -ForegroundColor White
    Write-Host "2. Open each .md file individually" -ForegroundColor White
    Write-Host "3. For each file, press Ctrl+Shift+P" -ForegroundColor White
    Write-Host "4. Type 'Markdown PDF: Export (pdf)' and press Enter" -ForegroundColor White
    Write-Host "5. The PDF will be created in the same directory" -ForegroundColor White
}

# Clean up temporary script
if (Test-Path "batch_convert.js") {
    Remove-Item "batch_convert.js" -Force
}

Write-Host "`nScript completed!" -ForegroundColor Green

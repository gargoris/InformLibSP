# Manual PDF conversion helper with step-by-step guidance
param(
    [string]$FileName = ""
)

Write-Host "=== MANUAL PDF CONVERSION HELPER ===" -ForegroundColor Green

# Navigate to docs if needed
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

if ($FileName -ne "") {
    # Convert specific file
    $targetFile = $mdFiles | Where-Object { $_.Name -like "*$FileName*" }
    if ($targetFile) {
        Write-Host "Opening file: $($targetFile.Name)" -ForegroundColor Cyan
        code $targetFile.FullName
        
        Write-Host "`n=== CONVERSION STEPS ===" -ForegroundColor Yellow
        Write-Host "1. The file is now open in VS Code" -ForegroundColor White
        Write-Host "2. Press Ctrl+Shift+P" -ForegroundColor White
        Write-Host "3. Type 'markdown pdf' and press Enter" -ForegroundColor White
        Write-Host "4. Wait for 'PDF exported successfully' message" -ForegroundColor White
        Write-Host "5. The PDF will appear in this directory" -ForegroundColor White
    } else {
        Write-Host "File not found: $FileName" -ForegroundColor Red
    }
} else {
    # Interactive mode
    Write-Host "Found $($mdFiles.Count) Markdown files:" -ForegroundColor Cyan
    
    for ($i = 0; $i -lt $mdFiles.Count; $i++) {
        Write-Host "  $($i + 1). $($mdFiles[$i].Name)" -ForegroundColor White
    }
    
    Write-Host "`nChoose conversion method:" -ForegroundColor Yellow
    Write-Host "A. Convert one file at a time (recommended)" -ForegroundColor White
    Write-Host "B. Open all files and convert manually" -ForegroundColor White
    Write-Host "C. Exit" -ForegroundColor Gray
    
    $choice = Read-Host "`nEnter your choice (A/B/C)"
    
    switch ($choice.ToUpper()) {
        "A" {
            Write-Host "`n=== ONE-BY-ONE CONVERSION ===" -ForegroundColor Green
            
            foreach ($file in $mdFiles) {
                Write-Host "`nProcessing: $($file.Name)" -ForegroundColor Cyan
                
                # Check if PDF already exists
                $pdfName = $file.Name -replace '\.md$', '.pdf'
                if (Test-Path $pdfName) {
                    Write-Host "  ✅ PDF already exists: $pdfName" -ForegroundColor Green
                    continue
                }
                
                Write-Host "  Opening file in VS Code..." -ForegroundColor Yellow
                code $file.FullName
                
                Write-Host "`n  STEPS TO CONVERT:" -ForegroundColor White
                Write-Host "  1. Press Ctrl+Shift+P" -ForegroundColor Gray
                Write-Host "  2. Type 'markdown pdf'" -ForegroundColor Gray
                Write-Host "  3. Press Enter" -ForegroundColor Gray
                Write-Host "  4. Wait for success message" -ForegroundColor Gray
                
                Read-Host "`n  Press Enter when PDF is created (or Ctrl+C to stop)"
                
                # Check if PDF was created
                if (Test-Path $pdfName) {
                    Write-Host "  ✅ Success: $pdfName created!" -ForegroundColor Green
                } else {
                    Write-Host "  ❌ PDF not found. Try again." -ForegroundColor Red
                }
            }
            
            Write-Host "`n🎉 All files processed!" -ForegroundColor Green
        }
        
        "B" {
            Write-Host "`n=== OPENING ALL FILES ===" -ForegroundColor Green
            Write-Host "Opening all MD files in VS Code..." -ForegroundColor Yellow
            
            foreach ($file in $mdFiles) {
                code $file.FullName
                Start-Sleep -Milliseconds 200
            }
            
            Write-Host "`nAll files opened! For each file:" -ForegroundColor Cyan
            Write-Host "1. Click on the file tab" -ForegroundColor White
            Write-Host "2. Press Ctrl+Shift+P" -ForegroundColor White
            Write-Host "3. Type 'markdown pdf' and press Enter" -ForegroundColor White
            Write-Host "4. Repeat for all files" -ForegroundColor White
        }
        
        "C" {
            Write-Host "Exiting..." -ForegroundColor Gray
            exit 0
        }
        
        default {
            Write-Host "Invalid choice. Please run the script again." -ForegroundColor Red
        }
    }
}

# Final status
Write-Host "`n=== CHECKING RESULTS ===" -ForegroundColor Cyan
$pdfFiles = Get-ChildItem -Filter "*.pdf"
Write-Host "PDFs found: $($pdfFiles.Count)" -ForegroundColor Green

if ($pdfFiles.Count -gt 0) {
    Write-Host "`nPDF files created:" -ForegroundColor Yellow
    foreach ($pdf in $pdfFiles) {
        Write-Host "  ✅ $($pdf.Name)" -ForegroundColor Green
    }
}

Write-Host "`nConversion helper completed!" -ForegroundColor Green

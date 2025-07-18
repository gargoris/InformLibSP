# Enhanced script to open all MD files and setup PDF conversion
Write-Host "=== ENHANCED MD -> PDF CONVERTER ===" -ForegroundColor Green

# Verify current location
$currentPath = Get-Location
Write-Host "Current location: $currentPath" -ForegroundColor Yellow

# Navigate to docs directory
if ($currentPath.Path.EndsWith("DAAD#")) {
    if (Test-Path "docs") {
        Set-Location "docs"
        Write-Host "Moved to docs directory" -ForegroundColor Green
    } else {
        Write-Host "ERROR: docs directory not found!" -ForegroundColor Red
        exit 1
    }
} elseif ($currentPath.Path.EndsWith("docs")) {
    Write-Host "Already in docs directory" -ForegroundColor Green
} else {
    Write-Host "ERROR: Please run from DAAD# directory or docs subdirectory" -ForegroundColor Red
    exit 1
}

# Get all markdown files
$mdFiles = Get-ChildItem -Filter "*.md" | Sort-Object Name
Write-Host "`nFound $($mdFiles.Count) Markdown files:" -ForegroundColor Cyan
foreach ($file in $mdFiles) {
    Write-Host "  - $($file.Name)" -ForegroundColor White
}

# Create .vscode directory and settings
if (-not (Test-Path ".vscode")) {
    New-Item -ItemType Directory -Path ".vscode" | Out-Null
}

# Enhanced PDF settings
$settings = @"
{
    "markdown-pdf.outputDirectory": "./",
    "markdown-pdf.outputDirectoryRelativePathFile": true,
    "markdown-pdf.includeDefaultStyles": true,
    "markdown-pdf.highlight": true,
    "markdown-pdf.breaks": false,
    "markdown-pdf.emoji": true,
    "markdown-pdf.displayHeaderFooter": true,
    "markdown-pdf.headerTemplate": "<div style='font-size:10px; margin-left:1cm; color:#666;'></div>",
    "markdown-pdf.footerTemplate": "<div style='font-size:10px; margin:0 auto; color:#666;'>Page <span class='pageNumber'></span> of <span class='totalPages'></span></div>",
    "markdown-pdf.printBackground": true,
    "markdown-pdf.orientation": "portrait",
    "markdown-pdf.format": "A4",
    "markdown-pdf.margin.top": "2cm",
    "markdown-pdf.margin.bottom": "2cm",
    "markdown-pdf.margin.right": "1.5cm",
    "markdown-pdf.margin.left": "1.5cm",
    "markdown-pdf.quality": 100,
    "files.encoding": "utf8"
}
"@

$settings | Out-File -FilePath ".vscode/settings.json" -Encoding UTF8
Write-Host "VS Code settings configured for optimal PDF generation" -ForegroundColor Green

# Open all MD files in VS Code
Write-Host "`nOpening all Markdown files in VS Code..." -ForegroundColor Yellow
foreach ($file in $mdFiles) {
    code $file.FullName
    Start-Sleep -Milliseconds 200  # Small delay to avoid overwhelming VS Code
}

Write-Host "`n=== CONVERSION INSTRUCTIONS ===" -ForegroundColor Cyan
Write-Host "METHOD 1 - Batch conversion:" -ForegroundColor White
Write-Host "1. In VS Code Explorer, select multiple .md files (Ctrl+Click)" -ForegroundColor Gray
Write-Host "2. Right-click -> 'Markdown PDF: Export (pdf)'" -ForegroundColor Gray

Write-Host "`nMETHOD 2 - Individual conversion:" -ForegroundColor White
Write-Host "1. Open any .md file" -ForegroundColor Gray
Write-Host "2. Press Ctrl+Shift+P" -ForegroundColor Gray
Write-Host "3. Type 'markdown pdf export'" -ForegroundColor Gray
Write-Host "4. Press Enter" -ForegroundColor Gray

Write-Host "`nMETHOD 3 - Command palette shortcut:" -ForegroundColor White
Write-Host "1. Press F1 or Ctrl+Shift+P" -ForegroundColor Gray
Write-Host "2. Type '> Markdown PDF: Export (pdf)'" -ForegroundColor Gray

Write-Host "`n=== PDF SETTINGS ===" -ForegroundColor Green
Write-Host "- Format: A4 with optimized margins" -ForegroundColor Gray
Write-Host "- Quality: Maximum (100)" -ForegroundColor Gray
Write-Host "- Features: Syntax highlighting, emojis, page numbers" -ForegroundColor Gray
Write-Host "- Encoding: UTF-8 for international characters" -ForegroundColor Gray

Write-Host "`nAll files opened! Ready for PDF conversion." -ForegroundColor Green

# Simple and reliable PDF converter for all MD files
Write-Host "=== SIMPLE MD TO PDF CONVERTER ===" -ForegroundColor Green

# Check if we're in the right directory
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
Write-Host "Found $($mdFiles.Count) Markdown files" -ForegroundColor Cyan

# List all files
Write-Host "`nFiles to convert:" -ForegroundColor White
foreach ($file in $mdFiles) {
    Write-Host "  $($file.Name)" -ForegroundColor Gray
}

Write-Host "`n=== EASY CONVERSION METHOD ===" -ForegroundColor Green
Write-Host "Follow these simple steps:" -ForegroundColor Yellow

Write-Host "`n1. OPEN VS CODE WORKSPACE:" -ForegroundColor Cyan
Write-Host "   Run this command: code ." -ForegroundColor White

Write-Host "`n2. FOR EACH FILE, DO THIS:" -ForegroundColor Cyan
Write-Host "   a) Click on any .md file in Explorer" -ForegroundColor White
Write-Host "   b) Press Ctrl+Shift+P" -ForegroundColor White
Write-Host "   c) Type: markdown pdf" -ForegroundColor White
Write-Host "   d) Select: Markdown PDF: Export (pdf)" -ForegroundColor White
Write-Host "   e) Wait for 'PDF exported successfully' message" -ForegroundColor White

Write-Host "`n3. BATCH METHOD (if it works for you):" -ForegroundColor Cyan
Write-Host "   a) In VS Code Explorer, select multiple .md files" -ForegroundColor White
Write-Host "   b) Right-click and look for 'Markdown PDF: Export (pdf)'" -ForegroundColor White
Write-Host "   c) If you don't see it, use individual method above" -ForegroundColor White

Write-Host "`n=== QUICK START ===" -ForegroundColor Green
Write-Host "Opening VS Code now..." -ForegroundColor Yellow

# Open VS Code in current directory
code .

Write-Host "`nVS Code opened! Now follow the steps above." -ForegroundColor Green
Write-Host "The PDFs will appear in this same directory." -ForegroundColor Yellow

# Create a simple checklist file
$checklist = @"
# PDF Conversion Checklist

Copy this list and check off each file as you convert it:

"@

foreach ($file in $mdFiles) {
    $checklist += "☐ $($file.Name)`n"
}

$checklist += @"

## Quick Steps:
1. Click on .md file
2. Ctrl+Shift+P
3. Type "markdown pdf"
4. Select "Markdown PDF: Export (pdf)"
5. Wait for success message
6. Check off the file above

## Files converted: 0 / $($mdFiles.Count)
"@

$checklist | Out-File -FilePath "PDF_Conversion_Checklist.txt" -Encoding UTF8
Write-Host "`nCreated checklist: PDF_Conversion_Checklist.txt" -ForegroundColor Green

Write-Host "`n🎯 TIP: Keep the checklist open to track your progress!" -ForegroundColor Cyan

# Script para abrir archivos Markdown y generar PDFs en VS Code
Write-Host "Abriendo archivos Markdown en VS Code..." -ForegroundColor Green

Set-Location "docs"

# Obtener todos los archivos .md
$files = Get-ChildItem "*.md"

Write-Host "Encontrados $($files.Count) archivos:" -ForegroundColor Yellow
foreach ($file in $files) {
    Write-Host "  - $($file.Name)" -ForegroundColor White
}

Write-Host "Abriendo en VS Code..." -ForegroundColor Green

# Abrir todos los archivos
foreach ($file in $files) {
    code $file.FullName
    Start-Sleep -Milliseconds 300
}

Write-Host "Archivos abiertos. Para generar PDFs:" -ForegroundColor Cyan
Write-Host "1. En VS Code: Ctrl+Shift+P" -ForegroundColor White
Write-Host "2. Buscar: Markdown PDF Export" -ForegroundColor White
Write-Host "3. Seleccionar: Export (pdf)" -ForegroundColor White

# Mostrar PDFs existentes
$pdfs = Get-ChildItem "*.pdf"
Write-Host "PDFs actuales: $($pdfs.Count)" -ForegroundColor Yellow

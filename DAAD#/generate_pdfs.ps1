# Script para generar PDFs desde archivos Markdown usando VS Code
# Requiere la extensión Markdown PDF instalada en VS Code

Write-Host "=== GENERADOR DE PDFs DESDE MARKDOWN - DAAD# ===" -ForegroundColor Green
Write-Host "Procesando archivos en el directorio docs..." -ForegroundColor Yellow

# Cambiar al directorio docs
Set-Location "docs"

# Obtener todos los archivos .md
$markdownFiles = Get-ChildItem "*.md"

Write-Host "Encontrados $($markdownFiles.Count) archivos Markdown:" -ForegroundColor Cyan
foreach ($file in $markdownFiles) {
    Write-Host "  - $($file.Name)" -ForegroundColor White
}

Write-Host "`nAbriendo archivos en VS Code..." -ForegroundColor Yellow

# Abrir todos los archivos en VS Code
foreach ($file in $markdownFiles) {
    $fullPath = (Resolve-Path $file.FullName).Path
    Write-Host "Abriendo: $($file.Name)" -ForegroundColor Green
    Start-Process "code" -ArgumentList "`"$fullPath`"" -NoNewWindow
    Start-Sleep -Milliseconds 500  # Pequeña pausa entre archivos
}

Write-Host "`n=== ARCHIVOS ABIERTOS EN VS CODE ===" -ForegroundColor Green
Write-Host "Para convertir cada archivo a PDF:" -ForegroundColor Yellow
Write-Host "1. En VS Code, presiona Ctrl+Shift+P" -ForegroundColor White
Write-Host "2. Escribe 'Markdown PDF: Export (pdf)'" -ForegroundColor White  
Write-Host "3. Presiona Enter para generar el PDF" -ForegroundColor White
Write-Host "4. Repite para cada archivo abierto" -ForegroundColor White

Write-Host "`nTambién puedes usar el método por lotes:" -ForegroundColor Cyan
Write-Host "1. Selecciona todos los archivos .md en el explorador de VS Code" -ForegroundColor White
Write-Host "2. Click derecho > 'Markdown PDF: Export (pdf)'" -ForegroundColor White

# Listar PDFs existentes
Write-Host "`nPDFs actualmente en el directorio:" -ForegroundColor Cyan
$pdfFiles = Get-ChildItem "*.pdf" -ErrorAction SilentlyContinue
if ($pdfFiles.Count -gt 0) {
    foreach ($pdf in $pdfFiles) {
        Write-Host "  ✓ $($pdf.Name)" -ForegroundColor Green
    }
} else {
    Write-Host "  (No hay PDFs aún)" -ForegroundColor Yellow
}

Write-Host "`n¡Proceso completado! Los archivos están listos para conversión." -ForegroundColor Green

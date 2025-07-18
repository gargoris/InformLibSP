# Script for automatic Markdown to PDF conversion using VS Code extension
Write-Host "=== AUTOMATIC MD -> PDF CONVERTER ===" -ForegroundColor Green

# Check if we're in the correct directory
$currentDir = Get-Location
if (-not $currentDir.Path.EndsWith("DAAD#")) {
    Write-Host "Error: Please run this script from the DAAD# directory" -ForegroundColor Red
    exit 1
}

# Change to docs directory
if (Test-Path "docs") {
    Set-Location "docs"
    Write-Host "Changed to docs directory" -ForegroundColor Yellow
} else {
    Write-Host "Error: docs directory not found" -ForegroundColor Red
    exit 1
}

# List all MD files first
Write-Host "`nFound Markdown files:" -ForegroundColor Cyan
Get-ChildItem -Filter "*.md" | ForEach-Object { Write-Host "  - $($_.Name)" -ForegroundColor White }

# Create .vscode directory if it doesn't exist
if (-not (Test-Path ".vscode")) {
    New-Item -ItemType Directory -Path ".vscode" | Out-Null
    Write-Host "Created .vscode directory" -ForegroundColor Yellow
}

# Create workspace configuration
$workspaceConfig = @{
    folders = @(
        @{
            path = "."
        }
    )
    extensions = @{
        recommendations = @("yzane.markdown-pdf")
    }
} | ConvertTo-Json -Depth 3

$workspaceConfig | Out-File -FilePath "daad-docs.code-workspace" -Encoding UTF8

Write-Host "Workspace created: daad-docs.code-workspace" -ForegroundColor Yellow
Write-Host "Opening workspace in VS Code..." -ForegroundColor Green

# Abrir el workspace
code "daad-docs.code-workspace"

Write-Host "`nInstrucciones para conversión en lotes:" -ForegroundColor Cyan
Write-Host "1. En VS Code, ve al Explorer (Ctrl+Shift+E)" -ForegroundColor White
Write-Host "2. Selecciona TODOS los archivos .md (Ctrl+A)" -ForegroundColor White
Write-Host "3. Click derecho sobre la selección" -ForegroundColor White
Write-Host "4. Busca 'Markdown PDF: Export (pdf)'" -ForegroundColor White
Write-Host "5. Los PDFs se generarán automáticamente" -ForegroundColor White

Write-Host "`nO método individual:" -ForegroundColor Cyan
Write-Host "1. Abre cualquier archivo .md" -ForegroundColor White
Write-Host "2. Ctrl+Shift+P" -ForegroundColor White
Write-Host "3. Escribe 'markdown pdf'" -ForegroundColor White
Write-Host "4. Selecciona 'Markdown PDF: Export (pdf)'" -ForegroundColor White

# Create PDF configuration for better quality
$pdfConfig = @"
{
    "markdown-pdf.outputDirectory": "./",
    "markdown-pdf.outputDirectoryRelativePathFile": true,
    "markdown-pdf.styles": [],
    "markdown-pdf.stylesRelativePathFile": true,
    "markdown-pdf.includeDefaultStyles": true,
    "markdown-pdf.highlight": true,
    "markdown-pdf.breaks": false,
    "markdown-pdf.emoji": true,
    "markdown-pdf.executablePath": "",
    "markdown-pdf.scale": 1,
    "markdown-pdf.displayHeaderFooter": true,
    "markdown-pdf.headerTemplate": "<div style='font-size:9px; margin-left:48px;'></div>",
    "markdown-pdf.footerTemplate": "<div style='font-size:9px; margin:0 auto;'><span class='pageNumber'></span> / <span class='totalPages'></span></div>",
    "markdown-pdf.printBackground": true,
    "markdown-pdf.orientation": "portrait",
    "markdown-pdf.pageRanges": "",
    "markdown-pdf.format": "A4",
    "markdown-pdf.width": "",
    "markdown-pdf.height": "",
    "markdown-pdf.margin.top": "1.5cm",
    "markdown-pdf.margin.bottom": "1cm",
    "markdown-pdf.margin.right": "1cm",
    "markdown-pdf.margin.left": "1cm"
}
"@

# Write settings to .vscode/settings.json
$pdfConfig | Out-File -FilePath ".vscode/settings.json" -Encoding UTF8
Write-Host "PDF configuration created in .vscode/settings.json" -ForegroundColor Green

# Open workspace in VS Code
Write-Host "Opening workspace in VS Code..." -ForegroundColor Green
code "daad-docs.code-workspace"

# Wait a moment for VS Code to open
Start-Sleep -Seconds 2

Write-Host "`nINSTRUCTIONS FOR BATCH CONVERSION:" -ForegroundColor Cyan
Write-Host "1. In VS Code, go to Explorer (Ctrl+Shift+E)" -ForegroundColor White
Write-Host "2. Select ALL .md files (Ctrl+A or select manually)" -ForegroundColor White
Write-Host "3. Right-click on the selection" -ForegroundColor White
Write-Host "4. Look for 'Markdown PDF: Export (pdf)'" -ForegroundColor White
Write-Host "5. PDFs will be generated automatically" -ForegroundColor White

Write-Host "`nOR INDIVIDUAL METHOD:" -ForegroundColor Cyan
Write-Host "1. Open any .md file" -ForegroundColor White
Write-Host "2. Press Ctrl+Shift+P" -ForegroundColor White
Write-Host "3. Type 'markdown pdf'" -ForegroundColor White
Write-Host "4. Select 'Markdown PDF: Export (pdf)'" -ForegroundColor White

Write-Host "`nOPTIMIZED PDF CONFIGURATION:" -ForegroundColor Green
Write-Host "- A4 format with proper margins" -ForegroundColor White
Write-Host "- Page numbers in footer" -ForegroundColor White
Write-Host "- Syntax highlighting enabled" -ForegroundColor White
Write-Host "- Emoji support enabled" -ForegroundColor White

Write-Host "`nScript completed successfully!" -ForegroundColor Green

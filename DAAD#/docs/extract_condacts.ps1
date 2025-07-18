# Script para extraer CondActs del manual DAAD y compararlos con implementación moderna

# Extraer todos los CondActs del documento de referencia
Get-Content "c:\Users\Francisco.Fuentes\inform\InformLibSP\DAAD#\docs\DAAD_CondActs_Reference.md" | 
    Select-String "\| (\d+) \| ([A-Z]+) \|" | 
    ForEach-Object {
        if ($_.Matches.Count -gt 0) {
            $_.Matches | ForEach-Object {
                $groups = $_.Groups
                if ($groups.Count -ge 3) {
                    "$($groups[1].Value),$($groups[2].Value)"
                }
            }
        }
    } | 
    Sort-Object { [int]($_.Split(',')[0]) } | 
    Out-File "c:\Users\Francisco.Fuentes\inform\InformLibSP\DAAD#\docs\condacts_extraidos.csv" -Encoding UTF8

Write-Host "CondActs extraídos y guardados en condacts_extraidos.csv"

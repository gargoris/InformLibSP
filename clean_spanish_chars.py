#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Script para limpiar caracteres españoles problemáticos de los archivos SpanishLib
y reemplazarlos con versiones compatibles con Inform 6
"""

import os
import re

# Mapeo de caracteres problemáticos
char_replacements = {
    # Vocales acentuadas
    'á': 'a', 'é': 'e', 'í': 'i', 'ó': 'o', 'ú': 'u',
    'Á': 'A', 'É': 'E', 'Í': 'I', 'Ó': 'O', 'Ú': 'U',
    
    # Consonantes especiales
    'ñ': 'n', 'Ñ': 'N', 'ü': 'u', 'Ü': 'U',
    
    # Signos de puntuación
    '¿': '?', '¡': '!',
    
    # Símbolos problemáticos
    '✅': '[OK]', '❌': '[X]', '⚠️': '[!]', '•': '-',
    
    # Otros caracteres problemáticos
    '"': '"', '"': '"', ''': "'", ''': "'",
    '–': '-', '—': '-', '…': '...'
}

def clean_file(filepath):
    """Limpia un archivo de caracteres problemáticos"""
    try:
        with open(filepath, 'r', encoding='utf-8') as f:
            content = f.read()
        
        original_content = content
        
        # Aplicar reemplazos
        for problematic, replacement in char_replacements.items():
            content = content.replace(problematic, replacement)
        
        # Solo escribir si hubo cambios
        if content != original_content:
            with open(filepath, 'w', encoding='utf-8') as f:
                f.write(content)
            print(f"✓ Limpiado: {filepath}")
            return True
        else:
            print(f"- Sin cambios: {filepath}")
            return False
            
    except Exception as e:
        print(f"✗ Error procesando {filepath}: {e}")
        return False

def main():
    """Procesa todos los archivos .h en SpanishLib"""
    base_dir = "SpanishLib"
    processed = 0
    changed = 0
    
    print("=== LIMPIEZA DE CARACTERES ESPAÑOLES ===")
    print("Reemplazando caracteres problemáticos con versiones compatibles...")
    print()
    
    for root, dirs, files in os.walk(base_dir):
        for file in files:
            if file.endswith('.h'):
                filepath = os.path.join(root, file)
                processed += 1
                if clean_file(filepath):
                    changed += 1
    
    print()
    print(f"=== RESUMEN ===")
    print(f"Archivos procesados: {processed}")
    print(f"Archivos modificados: {changed}")
    print()
    
    if changed > 0:
        print("✓ Limpieza completada. Los archivos ahora deberían compilar sin errores de caracteres.")
    else:
        print("- No se necesitaron cambios.")

if __name__ == "__main__":
    main()
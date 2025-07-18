# Script para agregar IDs a los CondActs
$condacts = @{
    0="AT"; 1="NOTAT"; 2="ATGT"; 3="ATLT"; 4="PRESENT"; 5="ABSENT"; 6="WORN"; 7="NOTWORN"; 8="CARRIED"; 9="NOTCARR";
    10="CHANCE"; 11="ZERO"; 12="NOTZERO"; 13="EQ"; 14="GT"; 15="LT"; 16="ADJECT1"; 17="ADVERB"; 18="SFX"; 19="DESC";
    20="QUIT"; 21="END"; 22="DONE"; 23="OK"; 24="ANYKEY"; 25="SAVE"; 26="LOAD"; 27="DPRINT"; 28="DISPLAY"; 29="CLS";
    30="DROPALL"; 31="AUTOG"; 32="AUTOD"; 33="AUTOW"; 34="AUTOR"; 35="PAUSE"; 36="SYNONYM"; 37="GOTO"; 38="MESSAGE"; 39="REMOVE";
    40="GET"; 41="DROP"; 42="WEAR"; 43="DESTROY"; 44="CREATE"; 45="SWAP"; 46="PLACE"; 47="SET"; 48="CLEAR"; 49="PLUS";
    50="MINUS"; 51="LET"; 52="NEWLINE"; 53="PRINT"; 54="SYSMESS"; 55="ISAT"; 56="SETCO"; 57="SPACE"; 58="HASAT"; 59="HASNAT";
    60="LISTOBJ"; 61="EXTERN"; 62="RAMSAVE"; 63="RAMLOAD"; 64="BEEP"; 65="PAPER"; 66="INK"; 67="BORDER"; 68="PREP"; 69="NOUN2";
    70="ADJECT2"; 71="ADD"; 72="SUB"; 73="PARSE"; 74="LISTAT"; 75="PROCESS"; 76="SAME"; 77="MES"; 78="WINDOW"; 79="NOTEQ";
    80="NOTSAME"; 81="MODE"; 82="WINAT"; 83="TIME"; 84="PICTURE"; 85="DOALL"; 86="MOUSE"; 87="GFX"; 88="ISNOTAT"; 89="WEIGH";
    90="PUTIN"; 91="TAKEOUT"; 92="NEWTEXT"; 93="ABILITY"; 94="WEIGHT"; 95="RANDOM"; 96="INPUT"; 97="SAVEAT"; 98="BACKAT"; 99="PRINTAT";
    100="WHATO"; 101="CALL"; 102="PUTO"; 103="NOTDONE"; 104="AUTOP"; 105="AUTOT"; 106="MOVE"; 107="WINSIZE"; 108="REDO"; 109="CENTRE";
    110="EXIT"; 111="INKEY"; 112="BIGGER"; 113="SMALLER"; 114="ISDONE"; 115="ISNDONE"; 116="SKIP"; 117="RESTART"; 118="TAB"; 119="COPYOF";
    121="COPYOO"; 123="COPYFO"; 125="COPYFF"; 126="COPYBF"; 127="RESET"
}

# Crear tabla inversa
$nameToId = @{}
foreach ($id in $condacts.Keys) {
    $nameToId[$condacts[$id]] = $id
}

# Leer archivo
$content = Get-Content "DAAD_CondActs_Reference.md" -Raw

# Procesar cada CondAct
foreach ($name in $nameToId.Keys) {
    $id = $nameToId[$name]
    
    # Patrones a buscar y reemplazar
    $patterns = @(
        "### $name locno\. ",
        "### $name locno\+ ",
        "### $name objno\. ",
        "### $name flagno\. ",
        "### $name mesno\. ",
        "### $name value ",
        "### $name word ",
        "### $name ",
        "### $name$"
    )
    
    foreach ($pattern in $patterns) {
        $replacement = $pattern -replace "### $name", "### $name (ID: $id)"
        $content = $content -replace $pattern, $replacement
    }
}

# Guardar archivo modificado
$content | Set-Content "DAAD_CondActs_Reference_with_IDs.md" -Encoding UTF8
Write-Host "Archivo procesado: DAAD_CondActs_Reference_with_IDs.md"

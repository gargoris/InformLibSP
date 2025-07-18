# Script final para agregar IDs de forma limpia
$idMap = @{
    "AT"=0; "NOTAT"=1; "ATGT"=2; "ATLT"=3; "PRESENT"=4; "ABSENT"=5; "WORN"=6; "NOTWORN"=7; "CARRIED"=8; "NOTCARR"=9;
    "CHANCE"=10; "ZERO"=11; "NOTZERO"=12; "EQ"=13; "GT"=14; "LT"=15; "ADJECT1"=16; "ADVERB"=17; "SFX"=18; "DESC"=19;
    "QUIT"=20; "END"=21; "DONE"=22; "OK"=23; "ANYKEY"=24; "SAVE"=25; "LOAD"=26; "DPRINT"=27; "DISPLAY"=28; "CLS"=29;
    "DROPALL"=30; "AUTOG"=31; "AUTOD"=32; "AUTOW"=33; "AUTOR"=34; "PAUSE"=35; "SYNONYM"=36; "GOTO"=37; "MESSAGE"=38; "REMOVE"=39;
    "GET"=40; "DROP"=41; "WEAR"=42; "DESTROY"=43; "CREATE"=44; "SWAP"=45; "PLACE"=46; "SET"=47; "CLEAR"=48; "PLUS"=49;
    "MINUS"=50; "LET"=51; "NEWLINE"=52; "PRINT"=53; "SYSMESS"=54; "ISAT"=55; "SETCO"=56; "SPACE"=57; "HASAT"=58; "HASNAT"=59;
    "LISTOBJ"=60; "EXTERN"=61; "RAMSAVE"=62; "RAMLOAD"=63; "BEEP"=64; "PAPER"=65; "INK"=66; "BORDER"=67; "PREP"=68; "NOUN2"=69;
    "ADJECT2"=70; "ADD"=71; "SUB"=72; "PARSE"=73; "LISTAT"=74; "PROCESS"=75; "SAME"=76; "MES"=77; "WINDOW"=78; "NOTEQ"=79;
    "NOTSAME"=80; "MODE"=81; "WINAT"=82; "TIME"=83; "PICTURE"=84; "DOALL"=85; "MOUSE"=86; "GFX"=87; "ISNOTAT"=88; "WEIGH"=89;
    "PUTIN"=90; "TAKEOUT"=91; "NEWTEXT"=92; "ABILITY"=93; "WEIGHT"=94; "RANDOM"=95; "INPUT"=96; "SAVEAT"=97; "BACKAT"=98; "PRINTAT"=99;
    "WHATO"=100; "CALL"=101; "PUTO"=102; "NOTDONE"=103; "AUTOP"=104; "AUTOT"=105; "MOVE"=106; "WINSIZE"=107; "REDO"=108; "CENTRE"=109;
    "EXIT"=110; "INKEY"=111; "BIGGER"=112; "SMALLER"=113; "ISDONE"=114; "ISNDONE"=115; "SKIP"=116; "RESTART"=117; "TAB"=118; "COPYOF"=119;
    "COPYOO"=121; "COPYFO"=123; "COPYFF"=125; "COPYBF"=126; "RESET"=127
}

# Usar el archivo de respaldo
$content = Get-Content "DAAD_CondActs_Reference_backup.md" -Raw

# Para cada CondAct, reemplazar solo la primera ocurrencia de la línea de título
foreach ($name in $idMap.Keys) {
    $id = $idMap[$name]
    
    # Buscar el patrón específico de título de CondAct (sin duplicar si ya tiene ID)
    $pattern = "### $name(?! \(ID:)([^\r\n]*)"
    $replacement = "### $name (ID: $id)`$1"
    
    $content = $content -replace $pattern, $replacement
}

# Guardar el resultado
$content | Set-Content "DAAD_CondActs_Reference.md" -Encoding UTF8 -NoNewline
Write-Host "IDs agregados exitosamente a todos los CondActs"

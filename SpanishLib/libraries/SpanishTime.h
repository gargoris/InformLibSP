! ==============================================================================
! SPANISHTIME.H - Sistema Completo de Gestión Temporal para Español
! Módulo avanzado del sistema modular Spanish Library para Inform 6
! Compatible con Inform 6.42 y librería estándar 6.12.7
! ==============================================================================

System_file;

#Ifndef SPANISH_TIME_INCLUDED;
Constant SPANISH_TIME_INCLUDED;
Constant SPANISH_TIME_VERSION = "1.0-complete";

! Verificación de dependencias
#Ifndef SPANISH_LIB_INCLUDED;
  Message fatalerror "*** Include Spanish.h antes de SpanishTime.h ***";
#Endif;

! ==============================================================================
! CONFIGURACIÓN DEL SISTEMA TEMPORAL
! ==============================================================================

! Características opcionales activables por el desarrollador
#Ifndef SPANISH_TIME_FEATURES;
    Constant SPANISH_TIME_BASIC;           ! Solo funciones básicas
    ! Constant SPANISH_TIME_CULTURAL;      ! Calendario cultural
    ! Constant SPANISH_TIME_REGIONAL;      ! Variantes regionales
    ! Constant SPANISH_TIME_ADVANCED;      ! Mecánicas avanzadas
#Endif;

! Configuración de región temporal por defecto
#Ifndef SPANISH_TIME_REGION;
    Constant SPANISH_TIME_REGION = 0;  ! 0=neutral, 1=México, 2=España, 3=Argentina
#Endif;

! ==============================================================================
! CONSTANTES TEMPORALES BÁSICAS
! ==============================================================================

! Unidades de tiempo
Constant SEGUNDO = 1;
Constant MINUTO = 60;
Constant HORA = 3600;
Constant DIA = 86400;
Constant SEMANA = 604800;

! Períodos del día
Constant MADRUGADA = 1;    ! 00:00 - 05:59
Constant MAÑANA = 2;       ! 06:00 - 11:59
Constant MEDIODIA = 3;     ! 12:00 - 12:59
Constant TARDE = 4;        ! 13:00 - 19:59
Constant NOCHE = 5;        ! 20:00 - 23:59

! Días de la semana
Constant LUNES = 1;
Constant MARTES = 2;
Constant MIERCOLES = 3;
Constant JUEVES = 4;
Constant VIERNES = 5;
Constant SABADO = 6;
Constant DOMINGO = 0;

! Meses del año
Constant ENERO = 1;    Constant FEBRERO = 2;   Constant MARZO = 3;
Constant ABRIL = 4;    Constant MAYO = 5;      Constant JUNIO = 6;
Constant JULIO = 7;    Constant AGOSTO = 8;    Constant SEPTIEMBRE = 9;
Constant OCTUBRE = 10; Constant NOVIEMBRE = 11; Constant DICIEMBRE = 12;

! Estaciones (Hemisferio Norte por defecto)
Constant PRIMAVERA = 1; Constant VERANO = 2;
Constant OTOÑO = 3;     Constant INVIERNO = 4;

! ==============================================================================
! VARIABLES GLOBALES DEL SISTEMA TEMPORAL
! ==============================================================================

! Tiempo actual del juego (en segundos desde inicio)
Global tiempo_juego = 0;

! Tiempo inicial del juego
Global hora_inicial = 8;     ! 8:00 AM por defecto
Global minuto_inicial = 0;
Global dia_inicial = 1;      ! Lunes por defecto
Global mes_inicial = 6;      ! Junio por defecto
Global año_inicial = 2024;

! Estado temporal actual
Global tiempo_pausado = false;
Global velocidad_tiempo = 1;  ! Multiplicador de velocidad

! Configuración cultural
Global formato_24_horas = false;  ! false = 12 horas, true = 24 horas
Global primer_dia_semana = LUNES; ! Primer día de la semana
Global hemisferio_sur = false;    ! Afecta estaciones

! ==============================================================================
! SISTEMA DE EXPRESIÓN TEMPORAL EN ESPAÑOL
! ==============================================================================

Array nombres_dias table
    "domingo" "lunes" "martes" "miércoles" 
    "jueves" "viernes" "sábado";

Array nombres_dias_cortos table
    "dom" "lun" "mar" "mié" "jue" "vie" "sáb";

Array nombres_meses table
    "enero" "febrero" "marzo" "abril" "mayo" "junio"
    "julio" "agosto" "septiembre" "octubre" "noviembre" "diciembre";

Array nombres_meses_cortos table
    "ene" "feb" "mar" "abr" "may" "jun"
    "jul" "ago" "sep" "oct" "nov" "dic";

Array nombres_estaciones table
    "primavera" "verano" "otoño" "invierno";

Array expresiones_tiempo table
    "al amanecer" "por la mañana" "al mediodía" "por la tarde"
    "al atardecer" "por la noche" "a medianoche" "de madrugada";

! ==============================================================================
! RUTINAS BÁSICAS DE TIEMPO
! ==============================================================================

[ TiempoInicializar hora minuto dia mes año;
    if (hora == 0) hora = hora_inicial;
    if (minuto == 0) minuto = minuto_inicial;
    if (dia == 0) dia = dia_inicial;
    if (mes == 0) mes = mes_inicial;
    if (año == 0) año = año_inicial;
    
    hora_inicial = hora;
    minuto_inicial = minuto;
    dia_inicial = dia;
    mes_inicial = mes;
    año_inicial = año;
    
    tiempo_juego = 0;
    tiempo_pausado = false;
    velocidad_tiempo = 1;
    
    #Ifdef DEBUG;
    print "[Tiempo inicializado: ";
    ImprimirHoraCompleta();
    print "]^";
    #Endif;
];

[ AvanzarTiempo segundos;
    if (tiempo_pausado) return;
    tiempo_juego = tiempo_juego + (segundos * velocidad_tiempo);
];

[ ObtenerHoraActual;
    return ((tiempo_juego / HORA) + hora_inicial) % 24;
];

[ ObtenerMinutoActual;
    return ((tiempo_juego + (minuto_inicial * MINUTO)) / MINUTO) % 60;
];

[ ObtenerDiaActual;
    local dias_transcurridos;
    dias_transcurridos = tiempo_juego / DIA;
    return (dia_inicial + dias_transcurridos) % 7;
];

[ ObtenerPeriodoDia;
    local hora = ObtenerHoraActual();
    
    if (hora >= 0 && hora <= 5) return MADRUGADA;
    if (hora >= 6 && hora <= 11) return MAÑANA;
    if (hora == 12) return MEDIODIA;
    if (hora >= 13 && hora <= 19) return TARDE;
    return NOCHE;
];

! ==============================================================================
! SISTEMA DE IMPRESIÓN TEMPORAL EN ESPAÑOL
! ==============================================================================

[ ImprimirHora formato;
    local hora = ObtenerHoraActual();
    local minuto = ObtenerMinutoActual();
    
    if (formato == 0) formato = formato_24_horas;
    
    if (formato) {
        ! Formato 24 horas
        if (hora == 1) print "Es la una";
        else { print "Son las "; print (LanguageNumber) hora; }
        
        if (minuto ~= 0) {
            if (minuto == 15) print " y cuarto";
            else if (minuto == 30) print " y media";
            else if (minuto == 45) print " menos cuarto";
            else if (minuto < 10) {
                print " y cero"; print (LanguageNumber) minuto;
            } else {
                print " y "; print (LanguageNumber) minuto;
            }
        }
    } else {
        ! Formato 12 horas
        local hora_12 = hora;
        if (hora_12 == 0) hora_12 = 12;
        if (hora_12 > 12) hora_12 = hora_12 - 12;
        
        if (hora_12 == 1) print "Es la una";
        else { print "Son las "; print (LanguageNumber) hora_12; }
        
        if (minuto ~= 0) {
            if (minuto == 15) print " y cuarto";
            else if (minuto == 30) print " y media";
            else if (minuto == 45) print " menos cuarto";
            else {
                print " y "; 
                if (minuto < 10) print "cero";
                print (LanguageNumber) minuto;
            }
        }
        
        ! Añadir AM/PM en español
        if (hora < 12) print " de la mañana";
        else if (hora == 12) print " del mediodía";
        else if (hora < 19) print " de la tarde";
        else print " de la noche";
    }
];

[ ImprimirDia;
    local dia = ObtenerDiaActual();
    print (string) nombres_dias-->dia;
];

[ ImprimirFecha completa;
    local dia_semana = ObtenerDiaActual();
    local mes = mes_inicial; ! Simplificado - podría calcularse
    local año = año_inicial;
    
    if (completa) {
        print (string) nombres_dias-->dia_semana, ", ";
    }
    
    print (LanguageNumber) 1; ! Día del mes - simplificado
    print " de ", (string) nombres_meses-->(mes-1);
    print " de ", (LanguageNumber) año;
];

[ ImprimirHoraCompleta;
    ImprimirDia();
    print ", ";
    ImprimirFecha(false);
    print ", ";
    ImprimirHora(0);
];

[ ImprimirPeriodoDia;
    local periodo = ObtenerPeriodoDia();
    
    switch(periodo) {
        MADRUGADA: print "madrugada";
        MAÑANA: print "mañana";
        MEDIODIA: print "mediodía";
        TARDE: print "tarde";
        NOCHE: print "noche";
    }
];

[ ImprimirMomento;
    local periodo = ObtenerPeriodoDia();
    
    switch(periodo) {
        MADRUGADA: print "de madrugada";
        MAÑANA: print "por la mañana";
        MEDIODIA: print "al mediodía";
        TARDE: print "por la tarde";
        NOCHE: print "por la noche";
    }
];

! ==============================================================================
! SISTEMA DE EVENTOS TEMPORALES
! ==============================================================================

! Estructura para eventos temporales
Class TiempoEvento
    with nombre "",
         hora_evento 0,
         minuto_evento 0,
         activo true,
         repetir false,  ! true para eventos recurrentes
         ejecutado false,
         accion_evento 0;

Array eventos_programados --> 20; ! Máximo 20 eventos
Global num_eventos = 0;

[ RegistrarEvento nombre hora minuto accion repetir;
    local evento;
    
    if (num_eventos >= 20) {
        print "[Error: Demasiados eventos programados]^";
        return false;
    }
    
    evento = TiempoEvento.create();
    evento.nombre = nombre;
    evento.hora_evento = hora;
    evento.minuto_evento = minuto;
    evento.accion_evento = accion;
    evento.repetir = repetir;
    evento.activo = true;
    evento.ejecutado = false;
    
    eventos_programados-->num_eventos = evento;
    num_eventos++;
    
    return evento;
];

[ ProcesarEventos;
    local i evento hora_actual minuto_actual;
    
    hora_actual = ObtenerHoraActual();
    minuto_actual = ObtenerMinutoActual();
    
    for (i = 0: i < num_eventos: i++) {
        evento = eventos_programados-->i;
        
        if (evento.activo && ~evento.ejecutado) {
            if (evento.hora_evento == hora_actual && 
                evento.minuto_evento == minuto_actual) {
                
                ! Ejecutar evento
                if (evento.accion_evento ~= 0) {
                    evento.accion_evento();
                }
                
                if (evento.repetir) {
                    evento.ejecutado = false; ! Se resetea para mañana
                } else {
                    evento.ejecutado = true;
                }
            }
        }
    }
];

! ==============================================================================
! SISTEMA CULTURAL Y REGIONAL
! ==============================================================================

#Ifdef SPANISH_TIME_CULTURAL;

! Días festivos y celebraciones
Array dias_festivos table
    ! Mes, Día, Nombre
    1 1 "Año Nuevo"
    1 6 "Día de Reyes"
    2 14 "San Valentín"
    5 1 "Día del Trabajo"
    12 25 "Navidad"
    12 31 "Nochevieja";

! Calendario religioso básico
Array calendario_religioso table
    ! Eventos móviles requerirían cálculo más complejo
    3 19 "San José"
    8 15 "Asunción"
    11 1 "Todos los Santos"
    11 2 "Día de los Muertos"
    12 8 "Inmaculada Concepción";

[ EsDiaFestivo mes dia;
    local i;
    for (i = 0: i < dias_festivos-->0: i = i + 3) {
        if (dias_festivos-->(i+1) == mes && 
            dias_festivos-->(i+2) == dia) {
            return dias_festivos-->(i+3);
        }
    }
    return 0;
];

[ ObtenerCelebracion;
    local celebracion = EsDiaFestivo(mes_inicial, 1); ! Simplificado
    if (celebracion) {
        print "Hoy es ", (string) celebracion;
        return true;
    }
    return false;
];

#Endif; ! SPANISH_TIME_CULTURAL

! ==============================================================================
! VARIANTES REGIONALES
! ==============================================================================

#Ifdef SPANISH_TIME_REGIONAL;

[ ConfigurarRegion region;
    switch(region) {
        1: ! México
            formato_24_horas = false;
            primer_dia_semana = DOMINGO;
            hemisferio_sur = false;
            
        2: ! España  
            formato_24_horas = true;
            primer_dia_semana = LUNES;
            hemisferio_sur = false;
            
        3: ! Argentina
            formato_24_horas = false;
            primer_dia_semana = LUNES;
            hemisferio_sur = true;
            
        default: ! Neutral
            formato_24_horas = false;
            primer_dia_semana = LUNES;
            hemisferio_sur = false;
    }
];

[ ImprimirHoraRegional;
    switch(SPANISH_TIME_REGION) {
        1: ! México - más informal
            print "Ahorita son las ";
            ImprimirHora(false);
            
        2: ! España - más formal
            print "Son las ";
            ImprimirHora(true);
            print " horas";
            
        3: ! Argentina
            print "Son las ";
            ImprimirHora(false);
            
        default:
            ImprimirHora(0);
    }
];

#Endif; ! SPANISH_TIME_REGIONAL

! ==============================================================================
! MECÁNICAS TEMPORALES AVANZADAS
! ==============================================================================

#Ifdef SPANISH_TIME_ADVANCED;

! Sistema de envejecimiento temporal
Global tiempo_envejecimiento = 0;

! Efectos temporales en objetos
[ EnvejecerObjeto obj tiempo;
    local edad;
    
    if (obj provides tiempo_creacion) {
        edad = tiempo_juego - obj.tiempo_creacion;
        
        ! Aplicar efectos según la edad
        if (edad > DIA * 7) { ! Una semana
            if (obj has comida) {
                obj.descripcion = "Ya no parece fresco.";
                give obj estropeado;
            }
        }
    }
];

! Sistema de fatiga temporal para NPCs
[ ActualizarFatiga persona;
    local hora = ObtenerHoraActual();
    
    if (persona provides fatiga) {
        if (hora >= 22 || hora <= 6) {
            persona.fatiga = persona.fatiga + 1;
        } else if (hora >= 8 && hora <= 10) {
            persona.fatiga = persona.fatiga - 2;
            if (persona.fatiga < 0) persona.fatiga = 0;
        }
    }
];

! Horarios de NPCs
[ EstaDisponible persona;
    local hora = ObtenerHoraActual();
    local periodo = ObtenerPeriodoDia();
    
    if (persona provides horario_trabajo) {
        return (hora >= persona.horario_inicio && 
                hora <= persona.horario_fin);
    }
    
    ! Horario general por defecto
    if (periodo == MADRUGADA) return false;
    if (periodo == NOCHE && random(100) > 30) return false;
    
    return true;
];

#Endif; ! SPANISH_TIME_ADVANCED

! ==============================================================================
! COMANDOS DE TIEMPO PARA EL JUGADOR
! ==============================================================================

[ ComandoTiempo;
    print "Hora actual: ";
    ImprimirHoraCompleta();
    print "^";
    
    print "Es ";
    ImprimirMomento();
    print ".^";
    
    #Ifdef SPANISH_TIME_CULTURAL;
    if (ObtenerCelebracion()) print "^";
    #Endif;
    
    rtrue;
];

[ ComandoEsperar minutos;
    local tiempo_espera;
    
    if (minutos == 0) minutos = 1;
    tiempo_espera = minutos * MINUTO;
    
    AvanzarTiempo(tiempo_espera);
    ProcesarEventos();
    
    print "Pasas ";
    if (minutos == 1) print "un minuto";
    else print (LanguageNumber) minutos, " minutos";
    print " esperando.^";
    
    print "Ahora son las ";
    ImprimirHora(0);
    print ".^";
    
    rtrue;
];

[ ComandoDormir horas;
    local tiempo_sueño;
    
    if (horas == 0) horas = 8;
    tiempo_sueño = horas * HORA;
    
    print "Te quedas dormido";
    if (horas > 1) {
        print " durante ", (LanguageNumber) horas, " horas";
    }
    print ".^";
    
    AvanzarTiempo(tiempo_sueño);
    ProcesarEventos();
    
    print "Despiertas. Ahora es ";
    ImprimirMomento();
    print " y son las ";
    ImprimirHora(0);
    print ".^";
    
    rtrue;
];

! ==============================================================================
! INTEGRACIÓN CON GRAMMAR Y VERBOS
! ==============================================================================

[ TiempoVerb;
    ComandoTiempo();
];

[ EsperarVerb;
    ComandoEsperar(noun);
];

[ DormirVerb;
    ComandoDormir(noun);
];

! Agregar a la gramática (ejemplo - requiere integración)
! Verb 'tiempo' 'hora' -> TiempoVerb;
! Verb 'esperar' * number -> EsperarVerb;
! Verb 'dormir' * -> DormirVerb;

! ==============================================================================
! RUTINAS DE UTILIDAD Y HELPERS
! ==============================================================================

[ CalcularDiferenciaTiempo tiempo1 tiempo2;
    return abs(tiempo1 - tiempo2);
];

[ EsMomento hora minuto margen;
    local hora_actual = ObtenerHoraActual();
    local minuto_actual = ObtenerMinutoActual();
    
    if (margen == 0) margen = 5; ! 5 minutos de margen
    
    return (hora_actual == hora && 
            abs(minuto_actual - minuto) <= margen);
];

[ TiempoDesdeMomento hora minuto;
    local hora_actual = ObtenerHoraActual();
    local minuto_actual = ObtenerMinutoActual();
    local diferencia;
    
    diferencia = ((hora_actual - hora) * 60) + (minuto_actual - minuto);
    return diferencia;
];

[ ProximoEvento;
    local i evento tiempo_evento tiempo_actual minimo_tiempo proximo;
    
    tiempo_actual = (ObtenerHoraActual() * 60) + ObtenerMinutoActual();
    minimo_tiempo = 9999;
    
    for (i = 0: i < num_eventos: i++) {
        evento = eventos_programados-->i;
        if (evento.activo && ~evento.ejecutado) {
            tiempo_evento = (evento.hora_evento * 60) + evento.minuto_evento;
            if (tiempo_evento > tiempo_actual && 
                tiempo_evento < minimo_tiempo) {
                minimo_tiempo = tiempo_evento;
                proximo = evento;
            }
        }
    }
    
    return proximo;
];

! ==============================================================================
! SISTEMA DE DEPURACIÓN TEMPORAL
! ==============================================================================

#Ifdef DEBUG;

[ DebugTiempo;
    print "^=== ESTADO DEL SISTEMA TEMPORAL ===^";
    print "Tiempo de juego: ", tiempo_juego, " segundos^";
    print "Hora actual: "; ImprimirHoraCompleta(); print "^";
    print "Período: "; ImprimirPeriodoDia(); print "^";
    print "Velocidad: x", velocidad_tiempo;
    if (tiempo_pausado) print " (PAUSADO)";
    print "^";
    print "Eventos activos: ", num_eventos, "^";
    
    #Ifdef SPANISH_TIME_REGIONAL;
    print "Región: ", SPANISH_TIME_REGION, "^";
    print "Formato 24h: "; if (formato_24_horas) print "Sí"; else print "No"; print "^";
    #Endif;
    
    print "================================^";
];

[ AcelerarTiempo factor;
    if (factor == 0) factor = 10;
    velocidad_tiempo = factor;
    print "[Tiempo acelerado x", factor, "]^";
];

[ PausarTiempo;
    tiempo_pausado = ~~tiempo_pausado;
    if (tiempo_pausado) print "[Tiempo pausado]^";
    else print "[Tiempo reanudado]^";
];

[ SimularEvento nombre;
    local i evento;
    
    for (i = 0: i < num_eventos: i++) {
        evento = eventos_programados-->i;
        if (evento.nombre == nombre) {
            print "[Simulando evento: ", (string) nombre, "]^";
            if (evento.accion_evento ~= 0) {
                evento.accion_evento();
            }
            return;
        }
    }
    print "[Evento no encontrado: ", (string) nombre, "]^";
];

#Endif; ! DEBUG

! ==============================================================================
! RUTINA DE INICIALIZACIÓN DEL MÓDULO
! ==============================================================================

[ SpanishTimeInitialise;
    ! Configuración regional automática
    #Ifdef SPANISH_TIME_REGIONAL;
    ConfigurarRegion(SPANISH_TIME_REGION);
    #Endif;
    
    ! Inicializar tiempo del juego
    TiempoInicializar(0, 0, 0, 0, 0);
    
    #Ifdef DEBUG;
    print "[SpanishTime v", (string) SPANISH_TIME_VERSION, " inicializado]^";
    
    #Ifdef SPANISH_TIME_CULTURAL;
    print "[✅ Calendario cultural activado]^";
    #Endif;
    
    #Ifdef SPANISH_TIME_REGIONAL;
    print "[✅ Variantes regionales activadas]^";
    #Endif;
    
    #Ifdef SPANISH_TIME_ADVANCED;
    print "[✅ Mecánicas avanzadas activadas]^";
    #Endif;
    
    print "[Hora inicial: ";
    ImprimirHoraCompleta();
    print "]^";
    #Endif;
];

! ==============================================================================
! HOOKS PARA INTEGRACIÓN CON EL JUEGO PRINCIPAL
! ==============================================================================

[ SpanishTimeHeartbeat;
    ! Llamar desde el heartbeat principal del juego
    ProcesarEventos();
    
    #Ifdef SPANISH_TIME_ADVANCED;
    ! Actualizar sistemas avanzados cada minuto de juego
    if ((tiempo_juego % MINUTO) == 0) {
        tiempo_envejecimiento++;
        ! Procesar envejecimiento, fatiga, etc.
    }
    #Endif;
];

[ SpanishTimeAfterEveryTurn;
    ! Llamar después de cada turno
    AvanzarTiempo(MINUTO * 1); ! 1 minuto por turno por defecto
    SpanishTimeHeartbeat();
];

! ==============================================================================
! CONSTANTES DE FINALIZACIÓN
! ==============================================================================

Constant SPANISH_TIME_LOADED;

#Ifdef SPANISH_MINIMAL;
Message warning "SpanishTime cargado en modo básico - activa SPANISH_TIME_CULTURAL y SPANISH_TIME_ADVANCED para características completas";
#Endif;

#Endif; ! SPANISH_TIME_INCLUDED

! ==============================================================================
! Fin de SpanishTime.h - Sistema Completo de Gestión Temporal para Español
! ==============================================================================
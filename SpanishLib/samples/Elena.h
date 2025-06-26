! ==============================================================================
! ELENA.H - NPC Romántico Complejo para demostrar sistema Spanish NPCs
! Ejemplo de implementación avanzada con seducción, personalidad compleja
! y evolución cultural realista
! ==============================================================================

! ==============================================================================
! ELENA VÁZQUEZ - ARTISTA ESPAÑOLA COMPLEJA
! ==============================================================================

SpanishNPC elena "Elena Vázquez" galeria
    with 
        ! Información básica
        name 'elena' 'vázquez' 'vazquez' 'artista' 'pintora' 'mujer',
        description [; ElenaNPC_Description(); ],
        
        ! Características lingüísticas específicas
        formality_level NPC_FORMAL,           ! Empieza formal
        personality_type PERSONALIDAD_INTELECTUAL,
        regional_variant REGION_ESPANA,
        
        ! Configuración social específica
        social_class 3,                       ! Clase media-alta
        educational_level 4,                  ! Universidad + estudios artísticos
        age_category 2,                       ! Adulta (28 años)
        
        ! Estado inicial de relación
        relationship_level RELACION_DESCONOCIDO,
        emotional_state EMOCION_NEUTRAL,
        
        ! Características especiales para romance
        trust_level 0,                        ! 0-100: confianza ganada
        artistic_appreciation 0,              ! 0-50: si el jugador aprecia arte
        intellectual_connection 0,            ! 0-50: conexión intelectual
        cultural_sensitivity 0,               ! 0-30: sensibilidad cultural
        personal_revelation_level 0,          ! 0-20: secretos compartidos
        
        ! Flags de estado romántico
        romance_available false,              ! Se activa con requisitos
        has_shared_past false,               ! Revelará algo personal
        is_vulnerable false,                 ! Estado emocional especial
        player_impressed_her false,          ! Logros que la impresionaron
        
        ! Obstáculos románticos
        has_artistic_block true,             ! Problema creativo actual
        worried_about_exhibition false,      ! Preocupación profesional
        skeptical_of_relationships true,     ! Desconfianza romántica inicial
        
        ! Contadores especiales
        deep_conversations 0,                ! Conversaciones profundas
        times_helped 0,                      ! Veces que el jugador la ayudó
        artistic_topics_discussed 0,        ! Temas artísticos conversados
        personal_space_violations 0,        ! Intentos prematuros de intimidad
        
        ! Rutinas personalizadas
        greet ElenaNPC_Greet,
        respond_to ElenaNPC_RespondTo,
        special_response ElenaNPC_SpecialResponse,
        check_romance_progress ElenaNPC_CheckRomanceProgress,
        
        ! Métodos de interacción específicos
        discuss_art ElenaNPC_DiscussArt,
        share_vulnerability ElenaNPC_ShareVulnerability,
        respond_to_compliment ElenaNPC_RespondToCompliment,
        react_to_help ElenaNPC_ReactToHelp,
        
    has female animate proper;

! ==============================================================================
! DESCRIPCIÓN DINÁMICA QUE EVOLUCIONA CON LA RELACIÓN
! ==============================================================================

[ ElenaNPC_Description;
    local relationship = elena.relationship_level;
    local trust = elena.trust_level;
    
    print "Elena es una mujer de veintiocho años con una presencia que ";
    print "inmediatamente sugiere refinamiento intelectual. ";
    
    if (relationship <= RELACION_CONOCIDO) {
        print "Tiene el cabello castaño recogido en un moño algo ";
        print "descuidado, como si estuviera más preocupada por sus ";
        print "pensamientos que por su apariencia. Sus ojos verdes ";
        print "observan con una mezcla de curiosidad e intensidad ";
        print "analítica. ";
    } else {
        print "Su cabello castaño enmarca un rostro expresivo que ";
        print "has llegado a conocer bien. Cuando te mira, sus ojos ";
        print "verdes reflejan una calidez que no mostaba inicialmente. ";
    }
    
    print "Lleva ropa que combina practicidad artística con ";
    print "elegancia sin esfuerzo: una blusa de lino blanco ";
    print "manchada discretamente de pintura y pantalones ";
    print "negros bien cortados.";
    
    if (relationship >= RELACION_AMIGABLE) {
        print " Notas que sus manos, delgadas y expresivas, ";
        print "están perpetuamente manchadas de pintura, un detalle ";
        print "que ahora encuentras encantador.";
    }
    
    if (trust > 50) {
        print "^^Hay momentos en que la has visto vulnerable, cuando ";
        print "su máscara de autocontrol se desliza ligeramente, ";
        print "revelando las dudas y pasiones que se ocultan bajo ";
        print "su exterior sereno.";
    }
    
    if (elena.is_vulnerable) {
        print "^^En este momento parece especialmente pensativa, ";
        print "casi melancólica, como si estuviera luchando con ";
        print "algo profundamente personal.";
    }
];

! ==============================================================================
! SISTEMA DE SALUDO EVOLUCIONARIO
! ==============================================================================

[ ElenaNPC_Greet context;
    local relationship = elena.relationship_level;
    local formality_changed;
    
    ! Actualizar formalidad dinámicamente
    formality_changed = SpanishNPC_UpdateFormality(elena, FormalityLevel, context);
    
    elena.conversation_count++;
    
    print "^";
    
    ! Diferentes saludos según progresión de relación
    switch (relationship) {
        RELACION_DESCONOCIDO:
            print "Elena levanta la vista de su lienzo con expresión ";
            print "ligeramente sorprendida. Sus modales son corteses ";
            print "pero reservados.^";
            print "^~Buenos días. ¿En qué puedo ayudarle?~ dice con ";
            print "formalidad educada, manteniendo cierta distancia.";
            
        RELACION_CONOCIDO:
            if (formality_changed) {
                print "Elena te sonríe con más naturalidad que antes.^";
                print "^~¡Hola! Me alegra verte de nuevo~ dice, y notas ";
                print "que ya no usa el 'usted'. ~¿Cómo has estado?~";
            } else {
                print "Elena deja su pincel y te saluda con una sonrisa ";
                print "genuina.^";
                print "^~¡Hola! Qué bueno verte~ dice cálidamente.";
            }
            
        RELACION_AMIGABLE:
            print "Los ojos de Elena se iluminan cuando te ve entrar.^";
            print "^~¡"; 
            print (name) player;
            print "! Precisamente estaba pensando en ti~ dice, ";
            print "acercándose con pasos ligeros. ~Tengo que contarte ";
            print "algo sobre lo que hemos estado hablando.~";
            
        RELACION_AMIGO:
            print "Elena deja inmediatamente lo que está haciendo ";
            print "cuando te ve, su rostro iluminándose con alegría ";
            print "auténtica.^";
            print "^~¡Por fin! He estado esperando que vinieras~ ";
            print "dice, casi corriendo hacia ti. ~Tengo tantas ";
            print "cosas que quiero compartir contigo.~";
            
        RELACION_INTIMO:
            if (elena.romance_available) {
                print "Elena se acerca a ti con una sonrisa que reserva ";
                print "solo para los momentos especiales entre ustedes.^";
                print "^~Hola, cariño~ dice suavemente, sus ojos ";
                print "buscando los tuyos con una intimidad que ";
                print "envía una corriente cálida por tu pecho.";
            }
    }
    
    print "^";
    
    ! Actualizar confianza ligeramente por interacción positiva
    ElenaNPC_AdjustTrust(2);
];

! ==============================================================================
! SISTEMA DE RESPUESTAS CONTEXTUAL COMPLEJO
! ==============================================================================

[ ElenaNPC_RespondTo topic emotional_context;
    local response_given = false;
    
    ! Establecer estado emocional
    elena.emotional_state = emotional_context;
    
    ! Respuestas específicas por temas
    switch (topic) {
        'arte', 'pintura', 'artista', 'creatividad':
            response_given = ElenaNPC_DiscussArt(emotional_context);
            
        'personal', 'vida', 'familia', 'pasado':
            response_given = ElenaNPC_ShareVulnerability(emotional_context);
            
        'trabajo', 'exposición', 'galería', 'carrera':
            response_given = ElenaNPC_DiscussProfessionalLife(emotional_context);
            
        'amor', 'relación', 'sentimientos', 'romance':
            response_given = ElenaNPC_DiscussRomance(emotional_context);
            
        'España', 'cultura', 'Madrid', 'tradición':
            response_given = ElenaNPC_DiscussCulture(emotional_context);
            
        default:
            response_given = ElenaNPC_GeneralResponse(topic, emotional_context);
    }
    
    ! Actualizar contadores según el tipo de conversación
    if (response_given) {
        if (topic == 'arte' or 'pintura' or 'creatividad') {
            elena.artistic_topics_discussed++;
            ElenaNPC_AdjustArtisticAppreciation(5);
        }
        if (topic == 'personal' or 'vida' or 'sentimientos') {
            elena.deep_conversations++;
            ElenaNPC_AdjustIntellectualConnection(3);
        }
    }
    
    return response_given;
];

! ==============================================================================
! CONVERSACIÓN ARTÍSTICA - CLAVE PARA CONECTAR CON ELENA
! ==============================================================================

[ ElenaNPC_DiscussArt emotional_context;
    local relationship = elena.relationship_level;
    local appreciation = elena.artistic_appreciation;
    
    print "^Elena se anima visiblemente cuando mencionas el arte.^";
    
    if (elena.has_artistic_block) {
        if (relationship <= RELACION_CONOCIDO) {
            print "^~El arte... sí, es toda mi vida~ dice, pero ";
            print "detectas una sombra que cruza por su expresión. ";
            print "~Aunque debo admitir que últimamente he estado ";
            print "pasando por un período... complicado. A veces ";
            print "la inspiración se esconde cuando más la necesitas.~";
            
        } else if (relationship >= RELACION_AMIGABLE) {
            print "^~¿Sabes qué?~ dice, bajando la voz como si ";
            print "compartiera un secreto. ~He estado luchando con ";
            print "un bloqueo creativo terrible. Es como si todas ";
            print "mis ideas se hubieran evaporado de repente.~ ";
            print "Sus ojos buscan los tuyos. ~¿Te ha pasado algo ";
            print "así? ¿Esa sensación de estar perdido en algo ";
            print "que antes te definía?~";
            
            elena.has_shared_past = true;
            ElenaNPC_AdjustTrust(8);
        }
    } else {
        if (appreciation < 20) {
            print "^~Para mí, el arte no es solo una profesión~ ";
            print "explica Elena, gesticulando graciosamente. ";
            print "~Es una forma de descifrar el mundo, de encontrar ";
            print "belleza en lugares inesperados. Cada pincelada ";
            print "es una conversación entre el alma y el lienzo.~";
            
        } else {
            print "^~Me encanta que aprecies el arte~ dice Elena ";
            print "con una sonrisa genuina. ~La mayoría de la gente ";
            print "mira una pintura y ve solo colores. Pero tú... ";
            print "tú realmente lo entiendes, ¿verdad? Ves las ";
            print "emociones, las historias no contadas.~";
            
            ElenaNPC_AdjustIntellectualConnection(7);
        }
    }
    
    ! Oportunidad para que el jugador responda
    print "^^[Puedes AYUDAR a Elena con su bloqueo, PREGUNTAR sobre ";
    print "su técnica, o COMPARTIR tu propia perspectiva artística]";
    
    return true;
];

! ==============================================================================
! VULNERABILIDAD Y CONEXIÓN EMOCIONAL
! ==============================================================================

[ ElenaNPC_ShareVulnerability emotional_context;
    local trust = elena.trust_level;
    local relationship = elena.relationship_level;
    
    if (trust < 30) {
        print "^Elena sonríe educadamente pero mantiene cierta ";
        print "distancia.^";
        print "^~Prefiero no hablar mucho de mi vida personal ";
        print "con... bueno, con gente que acabo de conocer. ";
        print "Espero que lo entiendas.~ Su tono es amable pero ";
        print "firme.";
        
        return true;
    }
    
    if (trust >= 30 && trust < 60) {
        print "^Elena te mira pensativamente, como evaluando ";
        print "si puede confiar en ti.^";
        print "^~¿Sabes? Vengo de una familia muy tradicional de ";
        print "Santander. Mi padre quería que fuera abogada, como ";
        print "él. Cuando les dije que quería ser artista...~ ";
        print "suspira. ~Digamos que no fue la conversación más ";
        print "fácil de mi vida. Todavía creen que es una 'fase'.~";
        
        elena.personal_revelation_level = elena.personal_revelation_level + 5;
        ElenaNPC_AdjustTrust(10);
        
    } else if (trust >= 60) {
        if (~~elena.is_vulnerable) {
            print "^Elena mira hacia la ventana, su expresión ";
            print "volviéndose melancólica.^";
            print "^~¿Puedo confesarte algo?~ dice suavemente. ";
            print "~A veces me siento como si estuviera viviendo ";
            print "dos vidas. La Elena que todos ven: exitosa, ";
            print "segura de sí misma, con todo bajo control... ";
            print "y la Elena real, que se despierta a las tres ";
            print "de la madrugada preguntándose si realmente ";
            print "vale la pena todo este esfuerzo.~";
            
            elena.is_vulnerable = true;
            elena.personal_revelation_level = elena.personal_revelation_level + 10;
            ElenaNPC_AdjustTrust(15);
            
            print "^^[Elena está siendo muy vulnerable contigo. ";
            print "Puedes CONSOLAR, COMPARTIR tu propia vulnerabilidad, ";
            print "o ESCUCHAR en silencio]";
        }
    }
    
    return true;
];

! ==============================================================================
! SISTEMA DE ROMANCE Y SEDUCCIÓN PROGRESIVA
! ==============================================================================

[ ElenaNPC_CheckRomanceProgress;
    local trust = elena.trust_level;
    local artistic = elena.artistic_appreciation;
    local intellectual = elena.intellectual_connection;
    local cultural = elena.cultural_sensitivity;
    local violations = elena.personal_space_violations;
    
    ! Requisitos para activar posibilidad romántica
    if (trust >= 50 && 
        artistic >= 25 && 
        intellectual >= 20 && 
        violations < 3 &&
        elena.deep_conversations >= 3) {
        
        if (~~elena.romance_available) {
            elena.romance_available = true;
            elena.skeptical_of_relationships = false;
            
            print "^[Sientes que tu relación con Elena ha alcanzado ";
            print "un punto especial. Hay una nueva calidez en sus ";
            print "miradas, una intimidad creciente en vuestras ";
            print "conversaciones.]";
            
            return true;
        }
    }
    
    return false;
];

[ ElenaNPC_RespondToCompliment type intensity;
    local relationship = elena.relationship_level;
    local trust = elena.trust_level;
    local violations = elena.personal_space_violations;
    
    switch (type) {
        1: ! Cumplido físico
            if (relationship < RELACION_AMIGABLE) {
                print "^Elena se sonroja ligeramente y desvía la mirada.^";
                print "^~Eh... gracias, supongo~ dice con cierta ";
                print "incomodidad. Es evidente que el cumplido la ";
                print "ha tomado por sorpresa.";
                
                elena.personal_space_violations++;
                ElenaNPC_AdjustTrust(-5);
                
            } else if (elena.romance_available) {
                print "^Elena sonríe con calidez, aceptando el cumplido ";
                print "con gracia.^";
                print "^~Eres muy amable~ dice, y hay algo nuevo en ";
                print "su mirada, una apreciación que va más allá de ";
                print "la simple cortesía.";
                
                ElenaNPC_AdjustTrust(3);
            }
            
        2: ! Cumplido intelectual/artístico
            print "^Los ojos de Elena se iluminan con placer genuino.^";
            print "^~Eso significa mucho viniendo de ti~ dice con ";
            print "sinceridad. ~No muchas personas entienden realmente ";
            print "lo que trato de expresar en mi trabajo.~";
            
            ElenaNPC_AdjustArtisticAppreciation(8);
            ElenaNPC_AdjustTrust(5);
            
        3: ! Cumplido sobre su personalidad
            if (trust >= 40) {
                print "^Elena te mira con una mezcla de sorpresa y ";
                print "gratitud.^";
                print "^~¿De verdad piensas eso?~ pregunta suavemente. ";
                print "~A veces siento que soy demasiado... intensa. ";
                print "Que pienso demasiado las cosas.~";
                
                ElenaNPC_AdjustIntellectualConnection(6);
                ElenaNPC_AdjustTrust(7);
            }
    }
];

[ ElenaNPC_ReactToHelp help_type;
    local relationship = elena.relationship_level;
    
    elena.times_helped++;
    
    switch (help_type) {
        1: ! Ayuda con bloqueo artístico
            if (elena.has_artistic_block) {
                print "^Elena te mira con asombro creciente.^";
                print "^~No puedo creer que... ¡sí! ¡Eso es exactamente ";
                print "lo que necesitaba escuchar!~ exclama, su rostro ";
                print "transformándose con nueva inspiración. ~Llevas ";
                print "razón. He estado tan obsesionada con ser perfecta ";
                print "que olvidé por qué empecé a pintar en primer lugar.~";
                
                elena.has_artistic_block = false;
                elena.player_impressed_her = true;
                ElenaNPC_AdjustTrust(15);
                ElenaNPC_AdjustIntellectualConnection(10);
                
                print "^^Te abraza espontáneamente, y por un momento ";
                print "sientes la calidez de su gratitud genuina.";
                
            }
            
        2: ! Ayuda emocional
            if (elena.is_vulnerable) {
                print "^Elena toma una respiración profunda, sus ojos ";
                print "brillando ligeramente.^";
                print "^~Gracias~ dice simplemente, pero hay una ";
                print "profundidad en esas palabras que resuena entre ";
                print "ustedes. ~No muchas personas saben cómo... ";
                print "simplemente estar presente cuando alguien lo ";
                print "necesita.~";
                
                elena.is_vulnerable = false;
                ElenaNPC_AdjustTrust(12);
                ElenaNPC_SetEmotion(elena, EMOCION_FELIZ, 0);
            }
    }
    
    ElenaNPC_CheckRomanceProgress();
];

! ==============================================================================
! GESTIÓN DE CONFIANZA Y MÉTRICAS ROMÁNTICAS
! ==============================================================================

[ ElenaNPC_AdjustTrust amount;
    elena.trust_level = elena.trust_level + amount;
    if (elena.trust_level < 0) elena.trust_level = 0;
    if (elena.trust_level > 100) elena.trust_level = 100;
    
    ! Actualizaciones automáticas de relación basadas en confianza
    if (elena.trust_level >= 80 && elena.relationship_level < RELACION_INTIMO) {
        SpanishNPC_UpdateRelationship(elena, 2);
    } else if (elena.trust_level >= 50 && elena.relationship_level < RELACION_AMIGO) {
        SpanishNPC_UpdateRelationship(elena, 1);
    }
];

[ ElenaNPC_AdjustArtisticAppreciation amount;
    elena.artistic_appreciation = elena.artistic_appreciation + amount;
    if (elena.artistic_appreciation < 0) elena.artistic_appreciation = 0;
    if (elena.artistic_appreciation > 50) elena.artistic_appreciation = 50;
];

[ ElenaNPC_AdjustIntellectualConnection amount;
    elena.intellectual_connection = elena.intellectual_connection + amount;
    if (elena.intellectual_connection < 0) elena.intellectual_connection = 0;
    if (elena.intellectual_connection > 50) elena.intellectual_connection = 50;
];

! ==============================================================================
! RESPUESTAS ESPECÍFICAS POR TEMAS
! ==============================================================================

[ ElenaNPC_DiscussProfessionalLife emotional_context;
    if (elena.worried_about_exhibition) {
        print "^Elena suspira, mostrando una vulnerabilidad poco común.^";
        print "^~Tengo una exposición importante el próximo mes~ ";
        print "confiesa. ~Es en una galería muy prestigiosa, y... ";
        print "bueno, podría cambiar toda mi carrera. Pero también ";
        print "podría ser un desastre total.~ Se ríe nerviosamente. ";
        print "~No ayuda que esté pasando por este bloqueo creativo.~";
        
        ElenaNPC_AdjustTrust(6);
    } else {
        print "^~Mi carrera ha sido un viaje interesante~ dice Elena ";
        print "reflexivamente. ~Cuando empecé, pensaba que el éxito ";
        print "sería solo cuestión de talento. Pero he aprendido que ";
        print "es igual de importante saber quién eres como artista ";
        print "y qué quieres decir al mundo.~";
    }
    
    return true;
];

[ ElenaNPC_DiscussRomance emotional_context;
    local relationship = elena.relationship_level;
    
    if (elena.skeptical_of_relationships) {
        print "^Elena se pone visiblemente incómoda.^";
        print "^~Honestly... he tenido algunas experiencias que me ";
        print "han hecho ser más cautelosa~ dice cuidadosamente. ";
        print "~En mi experiencia, las relaciones pueden ser... ";
        print "complicadas. Especialmente cuando eres una persona ";
        print "que necesita espacio para crear.~";
        
        elena.personal_space_violations++;
        
    } else if (elena.romance_available) {
        print "^Elena te mira con una nueva suavidad en sus ojos.^";
        print "^~¿Sabes? Solía pensar que el amor romántico era ";
        print "incompatible con la vida artística~ dice suavemente. ";
        print "~Pero últimamente... bueno, digamos que algunas ";
        print "personas han hecho que reconsidere esa perspectiva.~";
        
        ElenaNPC_AdjustTrust(5);
        
        print "^^[Elena está claramente hablando de ti. Este podría ";
        print "ser el momento para una DECLARACIÓN o para PROFUNDIZAR ";
        print "la conversación sobre vuestros sentimientos]";
    }
    
    return true;
];

[ ElenaNPC_DiscussCulture emotional_context;
    print "^Elena sonríe con orgullo genuino.^";
    print "^~España es un país de contrastes fascinantes~ dice ";
    print "con pasión. ~Tenemos esta rica herencia artística: ";
    print "Goya, Velázquez, Picasso... pero también una cultura ";
    print "contemporánea vibrante. Madrid especialmente tiene ";
    print "esta energía única donde lo tradicional y lo moderno ";
    print "se encuentran en cada esquina.~";
    
    ElenaNPC_AdjustCulturalSensitivity(5);
    ElenaNPC_AdjustIntellectualConnection(3);
    
    return true;
];

[ ElenaNPC_AdjustCulturalSensitivity amount;
    elena.cultural_sensitivity = elena.cultural_sensitivity + amount;
    if (elena.cultural_sensitivity < 0) elena.cultural_sensitivity = 0;
    if (elena.cultural_sensitivity > 30) elena.cultural_sensitivity = 30;
];

! ==============================================================================
! COMANDOS ESPECIALES PARA INTERACTUAR CON ELENA
! ==============================================================================

[ ElenaSeducirSub;
    if (elena notin location) {
        print "Elena no está aquí.";
        return;
    }
    
    if (elena.romance_available == false) {
        print "Elena retrocede ligeramente, claramente incómoda.^";
        print "^~Creo que me has malinterpretado~ dice con firmeza ";
        print "pero sin rudeza. ~Aprecio tu... interés, pero no ";
        print "estoy buscando ese tipo de relación en este momento.~";
        
        elena.personal_space_violations = elena.personal_space_violations + 2;
        ElenaNPC_AdjustTrust(-10);
        SpanishNPC_UpdateRelationship(elena, -1);
        return;
    }
    
    ! Romance disponible - respuesta positiva
    print "Elena te mira a los ojos, y por un momento el aire ";
    print "entre ustedes se espesa con posibilidades no dichas.^";
    print "^~"; print (name) player; print "...~ dice suavemente, ";
    print "tu nombre como una caricia. ~He estado sintiendo algo ";
    print "especial entre nosotros también. Pero... ¿estás seguro ";
    print "de esto? Porque cuando me entrego a algo, lo hago ";
    print "completamente.~";
    
    elena.relationship_level = RELACION_INTIMO;
    ElenaNPC_AdjustTrust(20);
    ElenaNPC_SetEmotion(elena, EMOCION_EMOCIONADO, 0);
    
    print "^^[¡Felicidades! Has conseguido conquistar el corazón ";
    print "de Elena a través de paciencia, comprensión y apreciación ";
    print "genuina por su arte y personalidad.]";
];

Verb 'seducir' 'conquistar' 'cortejar'
    * creature -> ElenaSeducirSub;

[ ElenaAyudarSub;
    if (elena notin location) {
        print "Elena no está aquí.";
        return;
    }
    
    if (elena.has_artistic_block) {
        print "^~¿Ayudarme?~ Elena te mira con curiosidad mezclada ";
        print "con esperanza. ~¿Qué tienes en mente?~^";
        print "^[Puedes sugerir que se RELAJE, que EXPLORE nuevas ";
        print "técnicas, o que RECUERDE por qué empezó a pintar]";
        
        ElenaNPC_ReactToHelp(1);
        return;
    }
    
    if (elena.worried_about_exhibition) {
        print "Elena te mira gratefully.^";
        print "^~Solo... gracias por preocuparte~ dice. ~A veces ";
        print "ayuda saber que alguien entiende la presión.~";
        
        ElenaNPC_AdjustTrust(5);
        return;
    }
    
    print "Elena sonríe cálidamente.^";
    print "^~Eres muy amable al ofrecerte, pero en este momento ";
    print "me siento bastante bien. Aunque aprecio mucho el gesto.~";
];

Verb 'ayudar' 'asistir' 'apoyar'
    * creature -> ElenaAyudarSub;

! ==============================================================================
! RUTINAS DE DEPURACIÓN PARA ELENA
! ==============================================================================

#Ifdef DEBUG;
[ ElenaDebugStatus;
    print "^=== ESTADO DE ELENA ===^";
    print "Confianza: ", elena.trust_level, "/100^";
    print "Apreciación artística: ", elena.artistic_appreciation, "/50^";
    print "Conexión intelectual: ", elena.intellectual_connection, "/50^";
    print "Sensibilidad cultural: ", elena.cultural_sensitivity, "/30^";
    print "Conversaciones profundas: ", elena.deep_conversations, "^";
    print "Veces ayudada: ", elena.times_helped, "^";
    print "Violaciones espacio personal: ", elena.personal_space_violations, "^";
    print "Romance disponible: ";
    if (elena.romance_available) print "SÍ"; else print "NO";
    print "^";
    print "Bloqueo artístico: ";
    if (elena.has_artistic_block) print "SÍ"; else print "NO";
    print "^";
    print "Es vulnerable: ";
    if (elena.is_vulnerable) print "SÍ"; else print "NO";
    print "^";
    print "========================^";
];

Verb meta 'elena_debug' 'elena_estado'
    * -> [ ; ElenaDebugStatus(); ];
#Endif;

! ==============================================================================
! LOCALIZACIÓN: GALERÍA DE ARTE
! ==============================================================================

Room galeria "Galería de Arte"
    with 
        description [;
            print "Esta galería íntima exhibe principalmente obras ";
            print "de artistas locales emergentes. Las paredes blancas ";
            print "están cuidadosamente iluminadas para resaltar las ";
            print "pinturas, y el suelo de madera pulida refleja ";
            print "suavemente las luces del techo.";
            
            if (elena in self) {
                print " Elena está trabajando en su caballete cerca ";
                print "de la ventana, aprovechando la luz natural.";
            }
        ],
        
        n_to pasillo_galeria,
        
    has light;

! Ejemplo de inicialización
[ InicializarElena;
    move elena to galeria;
    elena.has_artistic_block = true;
    elena.worried_about_exhibition = true;
    elena.skeptical_of_relationships = true;
    
    print "^[Elena Vázquez ha sido inicializada en la galería. ";
    print "Para conquistarla necesitarás: ";
    print "ganar su confianza (50+), apreciar su arte (25+), ";
    print "conectar intelectualmente (20+), tener 3+ conversaciones ";
    print "profundas, y evitar ser invasivo (<3 violaciones).]^";
];

! ==============================================================================
! Fin del ejemplo de Elena - NPC Romántico Complejo
! ==============================================================================
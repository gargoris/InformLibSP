! ==============================================================================
! ELENA.H - NPC Romantico Complejo para demostrar sistema Spanish NPCs
! Ejemplo de implementacion avanzada con seduccion, personalidad compleja
! y evolucion cultural realista
! ==============================================================================

! ==============================================================================
! ELENA VAZQUEZ - ARTISTA ESPANOLA COMPLEJA
! ==============================================================================

SpanishNPC elena "Elena Vazquez" galeria
    with 
        ! Informacion basica
        name 'elena' 'vazquez' 'vazquez' 'artista' 'pintora' 'mujer',
        description [; ElenaNPC_Description(); ],
        
        ! Caracteristicas linguisticas especificas
        formality_level NPC_FORMAL,           ! Empieza formal
        personality_type PERSONALIDAD_INTELECTUAL,
        regional_variant REGION_ESPANA,
        
        ! Configuracion social especifica
        social_class 3,                       ! Clase media-alta
        educational_level 4,                  ! Universidad + estudios artisticos
        age_category 2,                       ! Adulta (28 anos)
        
        ! Estado inicial de relacion
        relationship_level RELACION_DESCONOCIDO,
        emotional_state EMOCION_NEUTRAL,
        
        ! Caracteristicas especiales para romance
        trust_level 0,                        ! 0-100: confianza ganada
        artistic_appreciation 0,              ! 0-50: si el jugador aprecia arte
        intellectual_connection 0,            ! 0-50: conexion intelectual
        cultural_sensitivity 0,               ! 0-30: sensibilidad cultural
        personal_revelation_level 0,          ! 0-20: secretos compartidos
        
        ! Flags de estado romantico
        romance_available false,              ! Se activa con requisitos
        has_shared_past false,               ! Revelara algo personal
        is_vulnerable false,                 ! Estado emocional especial
        player_impressed_her false,          ! Logros que la impresionaron
        
        ! Obstaculos romanticos
        has_artistic_block true,             ! Problema creativo actual
        worried_about_exhibition false,      ! Preocupacion profesional
        skeptical_of_relationships true,     ! Desconfianza romantica inicial
        
        ! Contadores especiales
        deep_conversations 0,                ! Conversaciones profundas
        times_helped 0,                      ! Veces que el jugador la ayudo
        artistic_topics_discussed 0,        ! Temas artisticos conversados
        personal_space_violations 0,        ! Intentos prematuros de intimidad
        
        ! Rutinas personalizadas
        greet ElenaNPC_Greet,
        respond_to ElenaNPC_RespondTo,
        special_response ElenaNPC_SpecialResponse,
        check_romance_progress ElenaNPC_CheckRomanceProgress,
        
        ! Metodos de interaccion especificos
        discuss_art ElenaNPC_DiscussArt,
        share_vulnerability ElenaNPC_ShareVulnerability,
        respond_to_compliment ElenaNPC_RespondToCompliment,
        react_to_help ElenaNPC_ReactToHelp,
        
    has female animate proper;

! ==============================================================================
! DESCRIPCION DINAMICA QUE EVOLUCIONA CON LA RELACION
! ==============================================================================

[ ElenaNPC_Description;
    local relationship = elena.relationship_level;
    local trust = elena.trust_level;
    
    print "Elena es una mujer de veintiocho anos con una presencia que ";
    print "inmediatamente sugiere refinamiento intelectual. ";
    
    if (relationship <= RELACION_CONOCIDO) {
        print "Tiene el cabello castano recogido en un mono algo ";
        print "descuidado, como si estuviera mas preocupada por sus ";
        print "pensamientos que por su apariencia. Sus ojos verdes ";
        print "observan con una mezcla de curiosidad e intensidad ";
        print "analitica. ";
    } else {
        print "Su cabello castano enmarca un rostro expresivo que ";
        print "has llegado a conocer bien. Cuando te mira, sus ojos ";
        print "verdes reflejan una calidez que no mostaba inicialmente. ";
    }
    
    print "Lleva ropa que combina practicidad artistica con ";
    print "elegancia sin esfuerzo: una blusa de lino blanco ";
    print "manchada discretamente de pintura y pantalones ";
    print "negros bien cortados.";
    
    if (relationship >= RELACION_AMIGABLE) {
        print " Notas que sus manos, delgadas y expresivas, ";
        print "estan perpetuamente manchadas de pintura, un detalle ";
        print "que ahora encuentras encantador.";
    }
    
    if (trust > 50) {
        print "^^Hay momentos en que la has visto vulnerable, cuando ";
        print "su mascara de autocontrol se desliza ligeramente, ";
        print "revelando las dudas y pasiones que se ocultan bajo ";
        print "su exterior sereno.";
    }
    
    if (elena.is_vulnerable) {
        print "^^En este momento parece especialmente pensativa, ";
        print "casi melancolica, como si estuviera luchando con ";
        print "algo profundamente personal.";
    }
];

! ==============================================================================
! SISTEMA DE SALUDO EVOLUCIONARIO
! ==============================================================================

[ ElenaNPC_Greet context;
    local relationship = elena.relationship_level;
    local formality_changed;
    
    ! Actualizar formalidad dinamicamente
    formality_changed = SpanishNPC_UpdateFormality(elena, FormalityLevel, context);
    
    elena.conversation_count++;
    
    print "^";
    
    ! Diferentes saludos segun progresion de relacion
    switch (relationship) {
        RELACION_DESCONOCIDO:
            print "Elena levanta la vista de su lienzo con expresion ";
            print "ligeramente sorprendida. Sus modales son corteses ";
            print "pero reservados.^";
            print "^~Buenos dias. ?En que puedo ayudarle?~ dice con ";
            print "formalidad educada, manteniendo cierta distancia.";
            
        RELACION_CONOCIDO:
            if (formality_changed) {
                print "Elena te sonrie con mas naturalidad que antes.^";
                print "^~!Hola! Me alegra verte de nuevo~ dice, y notas ";
                print "que ya no usa el 'usted'. ~?Como has estado?~";
            } else {
                print "Elena deja su pincel y te saluda con una sonrisa ";
                print "genuina.^";
                print "^~!Hola! Que bueno verte~ dice calidamente.";
            }
            
        RELACION_AMIGABLE:
            print "Los ojos de Elena se iluminan cuando te ve entrar.^";
            print "^~!"; 
            print (name) player;
            print "! Precisamente estaba pensando en ti~ dice, ";
            print "acercandose con pasos ligeros. ~Tengo que contarte ";
            print "algo sobre lo que hemos estado hablando.~";
            
        RELACION_AMIGO:
            print "Elena deja inmediatamente lo que esta haciendo ";
            print "cuando te ve, su rostro iluminandose con alegria ";
            print "autentica.^";
            print "^~!Por fin! He estado esperando que vinieras~ ";
            print "dice, casi corriendo hacia ti. ~Tengo tantas ";
            print "cosas que quiero compartir contigo.~";
            
        RELACION_INTIMO:
            if (elena.romance_available) {
                print "Elena se acerca a ti con una sonrisa que reserva ";
                print "solo para los momentos especiales entre ustedes.^";
                print "^~Hola, carino~ dice suavemente, sus ojos ";
                print "buscando los tuyos con una intimidad que ";
                print "envia una corriente calida por tu pecho.";
            }
    }
    
    print "^";
    
    ! Actualizar confianza ligeramente por interaccion positiva
    ElenaNPC_AdjustTrust(2);
];

! ==============================================================================
! SISTEMA DE RESPUESTAS CONTEXTUAL COMPLEJO
! ==============================================================================

[ ElenaNPC_RespondTo topic emotional_context;
    local response_given = false;
    
    ! Establecer estado emocional
    elena.emotional_state = emotional_context;
    
    ! Respuestas especificas por temas
    switch (topic) {
        'arte', 'pintura', 'artista', 'creatividad':
            response_given = ElenaNPC_DiscussArt(emotional_context);
            
        'personal', 'vida', 'familia', 'pasado':
            response_given = ElenaNPC_ShareVulnerability(emotional_context);
            
        'trabajo', 'exposicion', 'galeria', 'carrera':
            response_given = ElenaNPC_DiscussProfessionalLife(emotional_context);
            
        'amor', 'relacion', 'sentimientos', 'romance':
            response_given = ElenaNPC_DiscussRomance(emotional_context);
            
        'Espana', 'cultura', 'Madrid', 'tradicion':
            response_given = ElenaNPC_DiscussCulture(emotional_context);
            
        default:
            response_given = ElenaNPC_GeneralResponse(topic, emotional_context);
    }
    
    ! Actualizar contadores segun el tipo de conversacion
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
! CONVERSACION ARTISTICA - CLAVE PARA CONECTAR CON ELENA
! ==============================================================================

[ ElenaNPC_DiscussArt emotional_context;
    local relationship = elena.relationship_level;
    local appreciation = elena.artistic_appreciation;
    
    print "^Elena se anima visiblemente cuando mencionas el arte.^";
    
    if (elena.has_artistic_block) {
        if (relationship <= RELACION_CONOCIDO) {
            print "^~El arte... si, es toda mi vida~ dice, pero ";
            print "detectas una sombra que cruza por su expresion. ";
            print "~Aunque debo admitir que ultimamente he estado ";
            print "pasando por un periodo... complicado. A veces ";
            print "la inspiracion se esconde cuando mas la necesitas.~";
            
        } else if (relationship >= RELACION_AMIGABLE) {
            print "^~?Sabes que?~ dice, bajando la voz como si ";
            print "compartiera un secreto. ~He estado luchando con ";
            print "un bloqueo creativo terrible. Es como si todas ";
            print "mis ideas se hubieran evaporado de repente.~ ";
            print "Sus ojos buscan los tuyos. ~?Te ha pasado algo ";
            print "asi? ?Esa sensacion de estar perdido en algo ";
            print "que antes te definia?~";
            
            elena.has_shared_past = true;
            ElenaNPC_AdjustTrust(8);
        }
    } else {
        if (appreciation < 20) {
            print "^~Para mi, el arte no es solo una profesion~ ";
            print "explica Elena, gesticulando graciosamente. ";
            print "~Es una forma de descifrar el mundo, de encontrar ";
            print "belleza en lugares inesperados. Cada pincelada ";
            print "es una conversacion entre el alma y el lienzo.~";
            
        } else {
            print "^~Me encanta que aprecies el arte~ dice Elena ";
            print "con una sonrisa genuina. ~La mayoria de la gente ";
            print "mira una pintura y ve solo colores. Pero tu... ";
            print "tu realmente lo entiendes, ?verdad? Ves las ";
            print "emociones, las historias no contadas.~";
            
            ElenaNPC_AdjustIntellectualConnection(7);
        }
    }
    
    ! Oportunidad para que el jugador responda
    print "^^[Puedes AYUDAR a Elena con su bloqueo, PREGUNTAR sobre ";
    print "su tecnica, o COMPARTIR tu propia perspectiva artistica]";
    
    return true;
];

! ==============================================================================
! VULNERABILIDAD Y CONEXION EMOCIONAL
! ==============================================================================

[ ElenaNPC_ShareVulnerability emotional_context;
    local trust = elena.trust_level;
    local relationship = elena.relationship_level;
    
    if (trust < 30) {
        print "^Elena sonrie educadamente pero mantiene cierta ";
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
        print "^~?Sabes? Vengo de una familia muy tradicional de ";
        print "Santander. Mi padre queria que fuera abogada, como ";
        print "el. Cuando les dije que queria ser artista...~ ";
        print "suspira. ~Digamos que no fue la conversacion mas ";
        print "facil de mi vida. Todavia creen que es una 'fase'.~";
        
        elena.personal_revelation_level = elena.personal_revelation_level + 5;
        ElenaNPC_AdjustTrust(10);
        
    } else if (trust >= 60) {
        if (~~elena.is_vulnerable) {
            print "^Elena mira hacia la ventana, su expresion ";
            print "volviendose melancolica.^";
            print "^~?Puedo confesarte algo?~ dice suavemente. ";
            print "~A veces me siento como si estuviera viviendo ";
            print "dos vidas. La Elena que todos ven: exitosa, ";
            print "segura de si misma, con todo bajo control... ";
            print "y la Elena real, que se despierta a las tres ";
            print "de la madrugada preguntandose si realmente ";
            print "vale la pena todo este esfuerzo.~";
            
            elena.is_vulnerable = true;
            elena.personal_revelation_level = elena.personal_revelation_level + 10;
            ElenaNPC_AdjustTrust(15);
            
            print "^^[Elena esta siendo muy vulnerable contigo. ";
            print "Puedes CONSOLAR, COMPARTIR tu propia vulnerabilidad, ";
            print "o ESCUCHAR en silencio]";
        }
    }
    
    return true;
];

! ==============================================================================
! SISTEMA DE ROMANCE Y SEDUCCION PROGRESIVA
! ==============================================================================

[ ElenaNPC_CheckRomanceProgress;
    local trust = elena.trust_level;
    local artistic = elena.artistic_appreciation;
    local intellectual = elena.intellectual_connection;
    local cultural = elena.cultural_sensitivity;
    local violations = elena.personal_space_violations;
    
    ! Requisitos para activar posibilidad romantica
    if (trust >= 50 && 
        artistic >= 25 && 
        intellectual >= 20 && 
        violations < 3 &&
        elena.deep_conversations >= 3) {
        
        if (~~elena.romance_available) {
            elena.romance_available = true;
            elena.skeptical_of_relationships = false;
            
            print "^[Sientes que tu relacion con Elena ha alcanzado ";
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
        1: ! Cumplido fisico
            if (relationship < RELACION_AMIGABLE) {
                print "^Elena se sonroja ligeramente y desvia la mirada.^";
                print "^~Eh... gracias, supongo~ dice con cierta ";
                print "incomodidad. Es evidente que el cumplido la ";
                print "ha tomado por sorpresa.";
                
                elena.personal_space_violations++;
                ElenaNPC_AdjustTrust(-5);
                
            } else if (elena.romance_available) {
                print "^Elena sonrie con calidez, aceptando el cumplido ";
                print "con gracia.^";
                print "^~Eres muy amable~ dice, y hay algo nuevo en ";
                print "su mirada, una apreciacion que va mas alla de ";
                print "la simple cortesia.";
                
                ElenaNPC_AdjustTrust(3);
            }
            
        2: ! Cumplido intelectual/artistico
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
                print "^~?De verdad piensas eso?~ pregunta suavemente. ";
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
        1: ! Ayuda con bloqueo artistico
            if (elena.has_artistic_block) {
                print "^Elena te mira con asombro creciente.^";
                print "^~No puedo creer que... !si! !Eso es exactamente ";
                print "lo que necesitaba escuchar!~ exclama, su rostro ";
                print "transformandose con nueva inspiracion. ~Llevas ";
                print "razon. He estado tan obsesionada con ser perfecta ";
                print "que olvide por que empece a pintar en primer lugar.~";
                
                elena.has_artistic_block = false;
                elena.player_impressed_her = true;
                ElenaNPC_AdjustTrust(15);
                ElenaNPC_AdjustIntellectualConnection(10);
                
                print "^^Te abraza espontaneamente, y por un momento ";
                print "sientes la calidez de su gratitud genuina.";
                
            }
            
        2: ! Ayuda emocional
            if (elena.is_vulnerable) {
                print "^Elena toma una respiracion profunda, sus ojos ";
                print "brillando ligeramente.^";
                print "^~Gracias~ dice simplemente, pero hay una ";
                print "profundidad en esas palabras que resuena entre ";
                print "ustedes. ~No muchas personas saben como... ";
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
! GESTION DE CONFIANZA Y METRICAS ROMANTICAS
! ==============================================================================

[ ElenaNPC_AdjustTrust amount;
    elena.trust_level = elena.trust_level + amount;
    if (elena.trust_level < 0) elena.trust_level = 0;
    if (elena.trust_level > 100) elena.trust_level = 100;
    
    ! Actualizaciones automaticas de relacion basadas en confianza
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
! RESPUESTAS ESPECIFICAS POR TEMAS
! ==============================================================================

[ ElenaNPC_DiscussProfessionalLife emotional_context;
    if (elena.worried_about_exhibition) {
        print "^Elena suspira, mostrando una vulnerabilidad poco comun.^";
        print "^~Tengo una exposicion importante el proximo mes~ ";
        print "confiesa. ~Es en una galeria muy prestigiosa, y... ";
        print "bueno, podria cambiar toda mi carrera. Pero tambien ";
        print "podria ser un desastre total.~ Se rie nerviosamente. ";
        print "~No ayuda que este pasando por este bloqueo creativo.~";
        
        ElenaNPC_AdjustTrust(6);
    } else {
        print "^~Mi carrera ha sido un viaje interesante~ dice Elena ";
        print "reflexivamente. ~Cuando empece, pensaba que el exito ";
        print "seria solo cuestion de talento. Pero he aprendido que ";
        print "es igual de importante saber quien eres como artista ";
        print "y que quieres decir al mundo.~";
    }
    
    return true;
];

[ ElenaNPC_DiscussRomance emotional_context;
    local relationship = elena.relationship_level;
    
    if (elena.skeptical_of_relationships) {
        print "^Elena se pone visiblemente incomoda.^";
        print "^~Honestly... he tenido algunas experiencias que me ";
        print "han hecho ser mas cautelosa~ dice cuidadosamente. ";
        print "~En mi experiencia, las relaciones pueden ser... ";
        print "complicadas. Especialmente cuando eres una persona ";
        print "que necesita espacio para crear.~";
        
        elena.personal_space_violations++;
        
    } else if (elena.romance_available) {
        print "^Elena te mira con una nueva suavidad en sus ojos.^";
        print "^~?Sabes? Solia pensar que el amor romantico era ";
        print "incompatible con la vida artistica~ dice suavemente. ";
        print "~Pero ultimamente... bueno, digamos que algunas ";
        print "personas han hecho que reconsidere esa perspectiva.~";
        
        ElenaNPC_AdjustTrust(5);
        
        print "^^[Elena esta claramente hablando de ti. Este podria ";
        print "ser el momento para una DECLARACION o para PROFUNDIZAR ";
        print "la conversacion sobre vuestros sentimientos]";
    }
    
    return true;
];

[ ElenaNPC_DiscussCulture emotional_context;
    print "^Elena sonrie con orgullo genuino.^";
    print "^~Espana es un pais de contrastes fascinantes~ dice ";
    print "con pasion. ~Tenemos esta rica herencia artistica: ";
    print "Goya, Velazquez, Picasso... pero tambien una cultura ";
    print "contemporanea vibrante. Madrid especialmente tiene ";
    print "esta energia unica donde lo tradicional y lo moderno ";
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
        print "Elena no esta aqui.";
        return;
    }
    
    if (elena.romance_available == false) {
        print "Elena retrocede ligeramente, claramente incomoda.^";
        print "^~Creo que me has malinterpretado~ dice con firmeza ";
        print "pero sin rudeza. ~Aprecio tu... interes, pero no ";
        print "estoy buscando ese tipo de relacion en este momento.~";
        
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
    print "especial entre nosotros tambien. Pero... ?estas seguro ";
    print "de esto? Porque cuando me entrego a algo, lo hago ";
    print "completamente.~";
    
    elena.relationship_level = RELACION_INTIMO;
    ElenaNPC_AdjustTrust(20);
    ElenaNPC_SetEmotion(elena, EMOCION_EMOCIONADO, 0);
    
    print "^^[!Felicidades! Has conseguido conquistar el corazon ";
    print "de Elena a traves de paciencia, comprension y apreciacion ";
    print "genuina por su arte y personalidad.]";
];

Verb 'seducir' 'conquistar' 'cortejar'
    * creature -> ElenaSeducirSub;

[ ElenaAyudarSub;
    if (elena notin location) {
        print "Elena no esta aqui.";
        return;
    }
    
    if (elena.has_artistic_block) {
        print "^~?Ayudarme?~ Elena te mira con curiosidad mezclada ";
        print "con esperanza. ~?Que tienes en mente?~^";
        print "^[Puedes sugerir que se RELAJE, que EXPLORE nuevas ";
        print "tecnicas, o que RECUERDE por que empezo a pintar]";
        
        ElenaNPC_ReactToHelp(1);
        return;
    }
    
    if (elena.worried_about_exhibition) {
        print "Elena te mira gratefully.^";
        print "^~Solo... gracias por preocuparte~ dice. ~A veces ";
        print "ayuda saber que alguien entiende la presion.~";
        
        ElenaNPC_AdjustTrust(5);
        return;
    }
    
    print "Elena sonrie calidamente.^";
    print "^~Eres muy amable al ofrecerte, pero en este momento ";
    print "me siento bastante bien. Aunque aprecio mucho el gesto.~";
];

Verb 'ayudar' 'asistir' 'apoyar'
    * creature -> ElenaAyudarSub;

! ==============================================================================
! RUTINAS DE DEPURACION PARA ELENA
! ==============================================================================

#Ifdef DEBUG;
[ ElenaDebugStatus;
    print "^=== ESTADO DE ELENA ===^";
    print "Confianza: ", elena.trust_level, "/100^";
    print "Apreciacion artistica: ", elena.artistic_appreciation, "/50^";
    print "Conexion intelectual: ", elena.intellectual_connection, "/50^";
    print "Sensibilidad cultural: ", elena.cultural_sensitivity, "/30^";
    print "Conversaciones profundas: ", elena.deep_conversations, "^";
    print "Veces ayudada: ", elena.times_helped, "^";
    print "Violaciones espacio personal: ", elena.personal_space_violations, "^";
    print "Romance disponible: ";
    if (elena.romance_available) print "SI"; else print "NO";
    print "^";
    print "Bloqueo artistico: ";
    if (elena.has_artistic_block) print "SI"; else print "NO";
    print "^";
    print "Es vulnerable: ";
    if (elena.is_vulnerable) print "SI"; else print "NO";
    print "^";
    print "========================^";
];

Verb meta 'elena_debug' 'elena_estado'
    * -> [ ; ElenaDebugStatus(); ];
#Endif;

! ==============================================================================
! LOCALIZACION: GALERIA DE ARTE
! ==============================================================================

Room galeria "Galeria de Arte"
    with 
        description [;
            print "Esta galeria intima exhibe principalmente obras ";
            print "de artistas locales emergentes. Las paredes blancas ";
            print "estan cuidadosamente iluminadas para resaltar las ";
            print "pinturas, y el suelo de madera pulida refleja ";
            print "suavemente las luces del techo.";
            
            if (elena in self) {
                print " Elena esta trabajando en su caballete cerca ";
                print "de la ventana, aprovechando la luz natural.";
            }
        ],
        
        n_to pasillo_galeria,
        
    has light;

! Ejemplo de inicializacion
[ InicializarElena;
    move elena to galeria;
    elena.has_artistic_block = true;
    elena.worried_about_exhibition = true;
    elena.skeptical_of_relationships = true;
    
    print "^[Elena Vazquez ha sido inicializada en la galeria. ";
    print "Para conquistarla necesitaras: ";
    print "ganar su confianza (50+), apreciar su arte (25+), ";
    print "conectar intelectualmente (20+), tener 3+ conversaciones ";
    print "profundas, y evitar ser invasivo (<3 violaciones).]^";
];

! ==============================================================================
! Fin del ejemplo de Elena - NPC Romantico Complejo
! ==============================================================================
# Sangre en la Penumbra
## Aventura Conversacional en DAAD Modernizado

```daad-modern
# Metadatos del juego
game {
  title: "Sangre en la Penumbra"
  author: "Aventurero DAAD"
  start: entrada_castillo
  max_score: 100
}

# Vocabulario del juego
vocab {
  # Verbos principales
  verbs: { 
    mirar: 1, examinar: 1, ver: 1,
    coger: 2, tomar: 2, agarrar: 2,
    dejar: 3, soltar: 3, 
    abrir: 4, 
    cerrar: 5,
    usar: 6, utilizar: 6,
    leer: 7,
    empujar: 8,
    tirar: 9, jalar: 9,
    mover: 10,
    hablar: 11, conversar: 11,
    dar: 12,
    encender: 13, prender: 13,
    apagar: 14,
    romper: 15, quebrar: 15,
    esconder: 16, ocultar: 16,
    buscar: 17,
    atacar: 18, golpear: 18
  }
  
  # Sustantivos importantes
  nouns: { 
    puerta: 50, portón: 50, 
    ventana: 51, 
    libro: 52, tomo: 52, 
    cruz: 53, crucifijo: 53, 
    espejo: 54, 
    agua: 55, 
    ajo: 56, ajos: 56, 
    diario: 57, 
    cortina: 58, cortinas: 58, 
    polvo: 59, 
    estaca: 60, 
    martillo: 61, mazo: 61, 
    llave: 62, 
    cuadro: 63, pintura: 63, retrato: 63, 
    vela: 64, candelabro: 64, 
    sangre: 65, 
    sarcófago: 66, ataúd: 66, 
    carta: 67, 
    armadura: 68, 
    escudo: 69,
    cáliz: 70, copa: 70,
    vino: 71,
    medallón: 72,
    cadena: 73,
    collar: 74,
    botella: 75,
    criado: 76, mayordomo: 76, igor: 76,
    vampiro: 77, conde: 77, nosferatu: 77,
    biblia: 78,
    mapa: 79
  }
  
  # Direcciones
  directions: { 
    norte: 10, n: 10, 
    sur: 11, s: 11, 
    este: 12, e: 12, 
    oeste: 13, o: 13, w: 13, 
    arriba: 14, subir: 14, 
    abajo: 15, bajar: 15, 
    entrar: 16, 
    salir: 17 
  }
  
  # Preposiciones
  prepositions: { 
    con: 100, 
    en: 101, 
    sobre: 102, 
    bajo: 103, debajo: 103,
    tras: 104, detrás: 104,
    dentro: 105,
    a: 106
  }
}

# LOCALIDADES
# ==========================================

location entrada_castillo {
  desc: "Te encuentras frente a un imponente castillo de piedra oscura. La noche se acerca rápidamente y las montañas circundantes proyectan sombras alargadas sobre el valle. Un camino de grava conduce a un portón de madera reforzado con hierro. El viento gélido silba entre las torres y almenas, como si el propio castillo respirara."
  exits: { 
    norte: puerta_principal,
    sur: camino_bosque
  }
}

location camino_bosque {
  desc: "El camino se adentra en un bosque de árboles retorcidos. La oscuridad entre los troncos parece impenetrable y te invade una sensación de ser observado. Quizás sería más prudente volver al castillo, donde al menos hay luz."
  exits: {
    norte: entrada_castillo
  }
  
  # Descripción alternativa cuando es de noche
  desc_noche: "La oscuridad ha caído por completo. El bosque es ahora un lugar de sombras y susurros amenazantes. No parece seguro adentrarse más. Algo se mueve entre los árboles... algo que está hambriento."
}

location puerta_principal {
  desc: "El gran vestíbulo del castillo te recibe con un espacio de techos altos y una escalera imponente que se bifurca hacia los pisos superiores. Candelabros antiguos proyectan una luz tenue y parpadeante. El suelo de mármol está pulido pero cubierto por una fina capa de polvo, como si los sirvientes hubieran abandonado hace tiempo sus labores. El eco de tus pasos resuena con inquietante claridad."
  exits: {
    sur: entrada_castillo,
    este: salon_principal,
    oeste: comedor,
    arriba: pasillo_superior
  }
}

location salon_principal {
  desc: "Un gran salón con muebles antiguos y tapices descoloridos. Una chimenea monumental domina la pared norte, pero sus cenizas están frías. Los retratos de la familia que adorna las paredes parecen seguirte con la mirada. Una sensación de melancolía impregna el ambiente."
  exits: {
    oeste: puerta_principal,
    norte: biblioteca
  }
  objects: [escudo, candelabro]
}

location comedor {
  desc: "Una larga mesa de roble ocupa el centro de esta habitación, preparada para una cena que parece nunca haber tenido lugar. Los cubiertos de plata están ennegrecidos y una fina capa de polvo cubre los platos. Las sillas están dispuestas como si esperaran invitados. En el centro de la mesa hay un candelabro y una botella de vino tinto, que parece demasiado reciente en comparación con el resto de la estancia."
  exits: {
    este: puerta_principal,
    sur: cocina
  }
  objects: [botella_vino, copa]
}

location cocina {
  desc: "Una cocina antigua con un gran horno de piedra y estantes llenos de utensilios oxidados. Manojos de ajo y hierbas secas cuelgan del techo. El ambiente huele a humedad y abandono, pero también hay un leve aroma de comida recién preparada, lo que resulta desconcertante dado el estado de abandono del lugar."
  exits: {
    norte: comedor
  }
  objects: [ajo, cuchillo]
}

location biblioteca {
  desc: "Estanterías repletas de libros antiguos desde el suelo hasta el techo. Una escalera móvil permite acceder a los volúmenes más altos. Un escritorio de caoba con una silla tapizada en terciopelo rojo ocupa el centro de la sala. Hay varios tomos abiertos sobre vampirismo y ocultismo. La luz de la luna se filtra a través de una ventana estrecha, iluminando motas de polvo suspendidas en el aire."
  exits: {
    sur: salon_principal,
    este: estudio_secreto
  }
  objects: [libro_vampiros, libro_historia_local]
}

location estudio_secreto {
  desc: "Un pequeño estudio oculto tras un panel giratorio en la biblioteca. Las paredes están cubiertas de mapas y diagramas de constelaciones. Un escritorio contiene un diario personal y varios documentos antiguos. Hay un espejo de cuerpo entero en una esquina, curiosamente intacto a pesar de la edad del lugar."
  exits: {
    oeste: biblioteca
  }
  objects: [diario_conde, espejo_plata, mapa_castillo]
}

location pasillo_superior {
  desc: "Un largo pasillo adornado con armaduras y tapices medievales. La alfombra, aunque desgastada, amortigua tus pasos. Puertas de madera tallada conducen a diferentes habitaciones. Al fondo del pasillo, una ventana muestra el cielo que se oscurece rápidamente."
  exits: {
    abajo: puerta_principal,
    norte: habitacion_invitados,
    sur: habitacion_conde
  }
  objects: [armadura]
}

location habitacion_invitados {
  desc: "Una habitación elegante pero inquietante. La cama con dosel está impecablemente hecha, con sábanas de lino fino. Un baúl de viaje abierto contiene tus pertenencias. Las cortinas ondean suavemente, aunque no hay brisa perceptible. Una vela solitaria sobre la mesita de noche proporciona la única iluminación."
  exits: {
    sur: pasillo_superior
  }
  objects: [crucifijo, carta_advertencia]
}

location habitacion_conde {
  desc: "La habitación principal del castillo, dominada por una imponente cama con dosel negro. Cortinas gruesas bloquean por completo la luz exterior. Un retrato del Conde en su juventud cuelga sobre una chimenea apagada. El ambiente es frío y opresivo. Una puerta pequeña parece conducir a un vestidor o pasaje."
  exits: {
    norte: pasillo_superior,
    abajo: pasaje_secreto
  }
  objects: [retrato_conde, medallón_antiguo]
}

location pasaje_secreto {
  desc: "Un estrecho pasadizo de piedra que desciende en espiral hacia las entrañas del castillo. Antorchas en soportes de hierro iluminan el camino, aunque no recuerdas haberlas encendido. El aire se vuelve más frío y húmedo conforme desciendes."
  exits: {
    arriba: habitacion_conde,
    abajo: cripta
  }
}

# OBJETOS ADICIONALES
# ==========================================

object cortinas_cripta {
  name: "cortinas pesadas"
  desc: "Gruesas cortinas de terciopelo que cubren parte de la pared de la cripta. Parecen fuera de lugar en un espacio tan antiguo y austero."
  location: cripta
  weight: 5
  takeable: false
}

object boton_oculto {
  name: "botón oculto"
  desc: "Un pequeño botón rojo oculto tras uno de los libros. Tiene una extraña inscripción en inglés que dice 'Who you gonna call?'"
  location: nowhere
  weight: 0
  takeable: false
}

# LOCALIDADES ACTUALIZADAS
# ==========================================

location cripta {
  desc: "Una cámara subterránea tallada en la roca viva. Nichos en las paredes contienen restos de la familia del Conde. En el centro de la sala, sobre una plataforma de mármol, descansa un sarcófago ornamentado de piedra negra. Inscripciones en un idioma desconocido cubren su superficie. El ambiente es de un frío sobrenatural. Unas pesadas cortinas cubren parte de la pared este."
  exits: {
    arriba: pasaje_secreto
  }
  objects: [sarcofago, candelabro_plata, cortinas_cripta]
}

# OBJETOS
# ==========================================

object libro_vampiros {
  name: "libro sobre vampiros"
  desc: "Un antiguo tomo encuadernado en cuero con el título 'Nosferatu: Leyendas de los No-Muertos'. Sus páginas amarillentas contienen ilustraciones detalladas sobre vampiros y métodos para combatirlos. Menciona la vulnerabilidad de estas criaturas a la luz solar, los símbolos religiosos, el ajo, y cómo solo pueden ser destruidos definitivamente con una estaca en el corazón."
  location: biblioteca
  weight: 2
  takeable: true
}

object libro_historia_local {
  name: "libro de historia local"
  desc: "Un volumen polvoriento sobre la historia de la región. Contiene un capítulo sobre el Castillo Drachenblut y su misterioso dueño, un noble extranjero que llegó hace un siglo y raramente se deja ver a la luz del día. Menciona desapariciones de aldeanos y extraños acontecimientos nocturnos."
  location: biblioteca
  weight: 2
  takeable: true
}

object diario_conde {
  name: "diario del Conde"
  desc: "Un diario personal encuadernado en piel roja con un broche de plata. Las entradas más recientes hablan de un 'invitado esperado' y 'preparativos para la transformación'. La caligrafía es elegante pero inquietantemente anticuada, como si quien escribiera hubiera aprendido en otro siglo."
  location: estudio_secreto
  weight: 1
  takeable: true
}

object espejo_plata {
  name: "espejo de plata"
  desc: "Un espejo de cuerpo entero con marco de plata labrada. El cristal es inusualmente claro para su aparente antigüedad. Cuando te miras en él, tu reflejo aparece normal, pero notas algo extraño: hay espacios vacíos donde deberían reflejarse ciertos objetos de la habitación."
  location: estudio_secreto
  weight: 10
  takeable: false
}

object mapa_castillo {
  name: "mapa del castillo"
  desc: "Un plano detallado del castillo, dibujado en pergamino amarillento. Muestra habitaciones y pasajes que no son evidentes a simple vista, incluyendo un pasadizo que conecta la habitación principal con una cripta subterránea."
  location: estudio_secreto
  weight: 1
  takeable: true
}

object crucifijo {
  name: "crucifijo de plata"
  desc: "Un crucifijo de plata con detalles finamente trabajados. A pesar de su antigüedad, brilla como si acabara de ser pulido. Sientes una extraña calidez al sostenerlo."
  location: habitacion_invitados
  weight: 1
  takeable: true
}

object carta_advertencia {
  name: "carta de advertencia"
  desc: "Una nota escrita apresuradamente en papel fino: 'Huya mientras pueda. El Conde no es lo que parece. No permanezca en el castillo después del anochecer. Si debe quedarse, no se separe de objetos benditos y mantenga el ajo cerca. No lo invite a entrar a su habitación bajo ninguna circunstancia.' La firma es ilegible, como si quien escribiera hubiera sido interrumpido."
  location: habitacion_invitados
  weight: 1
  takeable: true
}

object retrato_conde {
  name: "retrato del Conde"
  desc: "Un óleo que muestra a un hombre aristocrático de rostro pálido, ojos penetrantes y cabello negro peinado hacia atrás. La pintura parece tener siglos de antigüedad, pero el sujeto es idéntico al anfitrión que te recibió. Al mirar fijamente el retrato, tienes la inquietante sensación de que los ojos se mueven siguiéndote."
  location: habitacion_conde
  weight: 15
  takeable: false
}

object medallón_antiguo {
  name: "medallón antiguo"
  desc: "Un medallón de oro con un escudo de armas grabado. Al abrirlo, contiene un retrato en miniatura de una mujer joven que se parece asombrosamente a alguien que conoces. En el reverso hay una inscripción: 'Mi amor trasciende el tiempo y la muerte'."
  location: habitacion_conde
  weight: 1
  takeable: true
}

object sarcofago {
  name: "sarcófago ornamentado"
  desc: "Un elaborado ataúd de piedra negra con incrustaciones de plata. La tapa está decorada con símbolos ocultistas y la efigie del Conde. Parece extremadamente pesado, pero notas que podría abrirse."
  location: cripta
  weight: 500
  takeable: false
  closed: true
}

object candelabro_plata {
  name: "candelabro de plata"
  desc: "Un candelabro de plata maciza con velas de cera negra. Las velas están encendidas, aunque no hay señales de quién pudo haberlo hecho. La plata está extrañamente caliente al tacto."
  location: cripta
  weight: 3
  takeable: true
}

object estaca {
  name: "estaca de madera"
  desc: "Una estaca de madera de roble, afilada en un extremo. Parece haber sido tallada recientemente."
  location: nowhere
  weight: 1
  takeable: true
}

object martillo {
  name: "martillo"
  desc: "Un martillo pequeño pero pesado, ideal para trabajos que requieren precisión y fuerza."
  location: nowhere
  weight: 2
  takeable: true
}

object candelabro {
  name: "candelabro"
  desc: "Un candelabro de hierro forjado con velas parcialmente consumidas. Proporciona suficiente luz para ver en la oscuridad."
  location: salon_principal
  weight: 2
  takeable: true
}

object escudo {
  name: "escudo heráldico"
  desc: "Un escudo decorativo con el mismo emblema que viste en el medallón del Conde. Parece tener varios siglos de antigüedad."
  location: salon_principal
  weight: 8
  takeable: false
}

object armadura {
  name: "armadura medieval"
  desc: "Una armadura completa que permanece en posición vigilante. La visera del yelmo está bajada, como si escondiera el rostro de un ocupante invisible. Al examinarla más de cerca, notas que uno de los guanteletes sostiene una estaca de madera."
  location: pasillo_superior
  weight: 50
  takeable: false
}

object botella_vino {
  name: "botella de vino tinto"
  desc: "Una botella de cristal oscuro que contiene un líquido rojo intenso. La etiqueta muestra un emblema nobiliario y la fecha '1462'. El líquido es espeso y no parece comportarse exactamente como el vino normal."
  location: comedor
  weight: 1
  takeable: true
}

object copa {
  name: "copa de cristal"
  desc: "Una copa de cristal tallado, delicada y elegante. Contiene residuos de un líquido rojo que podría ser vino... o algo más."
  location: comedor
  weight: 1
  takeable: true
}

object ajo {
  name: "ristra de ajos"
  desc: "Un manojo de ajos secos colgados de una cuerda. Su olor es intenso y penetrante."
  location: cocina
  weight: 1
  takeable: true
}

object cuchillo {
  name: "cuchillo de cocina"
  desc: "Un cuchillo de cocina afilado con mango de madera. La hoja muestra signos de uso frecuente pero se mantiene bien afilada."
  location: cocina
  weight: 1
  takeable: true
}

# MENSAJES
# ==========================================

messages {
  bienvenida: "Año 1897. Tras recibir una misteriosa invitación, has llegado al remoto Castillo Drachenblut en las montañas de Transilvania. Como historiador aficionado, no pudiste resistir la oportunidad de visitar esta legendaria fortaleza. El Conde, tu anfitrión, te ha recibido cordialmente pero ha tenido que ausentarse 'por asuntos urgentes', dejándote explorar libremente el castillo. Sin embargo, mientras la noche se acerca, empiezas a sentir que algo siniestro acecha en las sombras...",
  amanecer: "Los primeros rayos del sol comienzan a filtrarse por las ventanas del castillo. Te sientes momentáneamente aliviado.",
  anochecer: "El sol se ha puesto por completo. La oscuridad envuelve el castillo y sientes una presencia maligna despertando. Debes tener cuidado ahora.",
  ataque_nocturno: "Te despiertas sobresaltado en medio de la noche. Una figura alta y pálida está inclinada sobre tu cama, con ojos rojos brillantes y colmillos expuestos. Es el Conde, pero ahora sabes que no es humano. Se acerca lentamente, hipnóticamente...",
  crucifijo_salva: "Instintivamente, levantas el crucifijo. La figura retrocede con un siseo de dolor y rabia. 'Esta noche te has salvado, pero no siempre estarás protegido', murmura antes de desvanecerse como niebla bajo la puerta.",
  sin_proteccion: "No tienes nada para defenderte. La figura se abalanza sobre ti con velocidad sobrenatural. Sientes un dolor agudo en el cuello y luego... oscuridad eterna.",
  entrada_cripta: "Al entrar en la cripta, sientes un frío sobrenatural que parece penetrar hasta tus huesos. Hay algo antiguo y maligno aquí.",
  abrir_sarcofago: "Con gran esfuerzo, logras deslizar la pesada tapa del sarcófago. En su interior, sobre un lecho de tierra de su país natal, yace el Conde, inmóvil y pálido como mármol. Ahora es tu oportunidad.",
  estaca_corazon: "Con determinación, colocas la estaca sobre el pecho del vampiro dormido y golpeas con fuerza usando el martillo. La estaca penetra y un grito inhumano resuena por toda la cripta. El cuerpo del Conde se convulsiona violentamente y luego se desintegra, convirtiéndose en polvo ante tus ojos.",
  victoria: "¡Has destruido al vampiro! Mientras recoges tus pertenencias para abandonar este lugar maldito, sientes que has librado al mundo de una antigua maldad. Los aldeanos te recordarán como un héroe, aunque nunca creerán completamente tu historia.",
  muerte_tiempo: "El tiempo se ha agotado. No has logrado destruir al vampiro antes del anochecer. Mientras la oscuridad cae, sientes su presencia acercándose inexorablemente. Esta vez, no hay escapatoria.",
  reflejo_ausente: "Al mirar en el espejo, notas algo extraordinario: ¡puedes ver toda la habitación reflejada, pero no hay señal del Conde que está parado justo a tu lado! La realización te golpea como un rayo: tu anfitrión es realmente un nosferatu, un no-muerto que no proyecta reflejo.",
  encuentra_estaca: "Examinas la armadura más de cerca y descubres que en su guantelete metálico sostiene una estaca de madera de roble, afilada y lista para ser usada.",
  martillo_armadura: "Al inspeccionar más detalladamente la base de la armadura, encuentras un pequeño martillo que probablemente se usaba para reparaciones menores en la pieza. Podría ser útil junto con la estaca.",
  encuentra_pasaje: "Siguiendo las indicaciones del mapa, presionas una serie de ornamentos en la pared. Con un chirrido metálico, un panel se desliza revelando un pasaje secreto que desciende a las profundidades del castillo.",
  libro_conocimiento: "Pasas horas estudiando el libro sobre vampiros. Ahora sabes que estas criaturas temen a los símbolos religiosos, el ajo y la luz solar. Son más poderosos por la noche y solo pueden ser destruidos definitivamente con una estaca en el corazón mientras descansan en su ataúd durante el día.",
  decapitacion_vampiro: "Con un movimiento rápido y decidido, usas el cuchillo para separar la cabeza del cuerpo del vampiro. A pesar de su filo común, la hoja corta con sorprendente facilidad, como si el no-muerto fuera más frágil de lo que aparenta. La cabeza se separa con un sonido seco y ambas partes comienzan a marchitarse rápidamente.",
  victoria_decapitacion: "Has destruido al vampiro mediante decapitación, un método menos conocido pero igualmente efectivo según los textos antiguos. Mientras abandonas el castillo, llevas contigo el conocimiento de haber eliminado una antigua amenaza, aunque el recuerdo de lo ocurrido te perseguirá para siempre.",
  luz_solar_cripta: "Tirando con fuerza de las pesadas cortinas, descubres que hay una claraboya oculta que da directamente a la cripta. Un rayo de sol entra directamente e impacta sobre el cuerpo inerte del vampiro. Instantáneamente, su piel comienza a humear y arder. El cuerpo se contorsiona en agonía silenciosa mientras se convierte en cenizas ante tus ojos.",
  victoria_luz: "Has destruido al vampiro exponiendo su cuerpo a la luz purificadora del sol. La amenaza ha terminado y puedes abandonar el castillo con la satisfacción de haber liberado al mundo de este mal ancestral. Sin embargo, una parte de ti se pregunta si realmente era el último de su especie...",
  beber_sangre_vampiro: "Impulsado por una curiosidad morbosa y una extraña atracción, te inclinas sobre el cuerpo inmóvil del vampiro. Una pequeña herida en su pecho rezuma un líquido oscuro y espeso. Casi sin pensarlo, pasas tu dedo por ella y pruebas la sangre. Un sabor metálico y dulce inunda tus sentidos, seguido de una sensación de ardor que se extiende por todo tu cuerpo. Sientes cambios comenzando dentro de ti...",
  beber_copa_sangre: "Llevado por una curiosidad irresistible, bebes el contenido de la copa. El líquido es espeso y tiene un sabor metálico, pero extrañamente agradable. Inmediatamente sientes un calor que se extiende por tu cuerpo, seguido de una claridad de sentidos que nunca habías experimentado. Los sonidos del castillo son ahora más nítidos, y puedes percibir olores que antes pasaban desapercibidos. Algo ha cambiado en ti.",
  dormir_sarcofago: "Te recuestas en el sarcófago, sobre la misma tierra donde descansaba el Conde. Un sopor irresistible te invade mientras sientes cómo tu humanidad se desvanece lentamente. Tu corazón late cada vez más despacio hasta que, finalmente, se detiene por completo. Pero tú sigues consciente.",
  final_vampiro: "Has abrazado la oscuridad y te has convertido en un vampiro. Tu antigua vida queda atrás mientras te adaptas a tu nueva existencia como criatura de la noche. El castillo es ahora tu hogar, y los siglos venideros serán testigos de tu reinado como el nuevo señor de Drachenblut. La sed de sangre será tu eterna compañera, junto con el poder y la inmortalidad que has ganado... a cambio de tu alma.",
  oferta_vampiro: "El Conde te mira fijamente, sus ojos rojos brillando en la penumbra. 'Veo potencial en ti', dice con voz suave pero autoritaria. 'Podrías unirte a mí, compartir la eternidad y el poder que confiere. Serías mi aliado, no mi víctima. Piénsalo... conocimiento ilimitado, tiempo sin fin para estudiar los secretos del mundo. Todo lo que debes hacer es aceptar mi regalo.' Extiende su mano pálida hacia ti, esperando tu respuesta.",
  aceptar_pacto: "Tras un momento de reflexión, extiendes tu mano y tomas la del Conde. Su piel es fría pero su agarre firme. Con un movimiento rápido, te atrae hacia él y sientes sus colmillos penetrando tu cuello. El dolor inicial da paso a una extraña euforia mientras tu vida se drena lentamente. Justo antes de perder la consciencia, él corta su propia muñeca y presiona la herida contra tus labios. El sabor de su sangre ancestral sella el pacto.",
  final_alianza: "Te has convertido en el aprendiz y aliado del Conde. Bajo su tutela, aprendes los secretos de la inmortalidad y los poderes que conlleva. Con el tiempo, estableces tu propio dominio en tierras cercanas, siempre manteniendo un pacto de no agresión con tu maestro. La eternidad se abre ante ti, llena de posibilidades oscuras pero fascinantes. Tu nombre será recordado en susurros temerosos durante siglos.",
  descubrir_cortinas: "Examinando las paredes de la cripta, notas que lo que parecían ser simples tapices decorativos son en realidad cortinas gruesas. Algo parece ocultarse tras ellas.",
  intentar_escapar: "Después de descubrir la verdadera naturaleza del Conde, decides que lo más sensato es huir del castillo inmediatamente. Recoges tus pertenencias esenciales y te diriges hacia la salida.",
  escape_exitoso: "Aprovechando la luz del día, logras abandonar el castillo y descender rápidamente por el camino hacia el pueblo más cercano. Aunque has escapado con vida, la experiencia te ha marcado para siempre. Nunca más volverás a sentirte completamente seguro en la oscuridad, y el recuerdo de los ojos rojos del Conde te perseguirá en tus pesadillas.",
  escape_fallido: "Mientras intentas salir del castillo, una figura aparece bloqueando tu camino. El Conde te observa con una sonrisa que revela sus colmillos. 'Nadie abandona mi castillo sin mi permiso', susurra. Antes de que puedas reaccionar, se abalanza sobre ti con velocidad sobrenatural.",
  descubrir_boton: "Mientras examinas minuciosamente los libros en la biblioteca, tu mano roza accidentalmente un mecanismo oculto tras un viejo tomo. Con un suave 'clic', un pequeño panel se desliza revelando un botón rojo con una extraña inscripción en inglés: 'Who you gonna call?'",
  pulsar_boton: "Con curiosidad, presionas el botón. Por un momento no ocurre nada, pero luego escuchas un extraño sonido a lo lejos, como una sirena peculiar acercándose rápidamente. El ruido se intensifica hasta que, de repente, las puertas del castillo se abren de golpe.",
  llegada_ghostbusters: "¡Cuatro hombres irrumpen en el castillo portando extraños aparatos y uniformes beige con un símbolo de un fantasma tachado! 'Somos los Cazafantasmas', anuncia el líder con gafas. 'Recibimos una llamada sobre una infestación de Tipo 4... ¿vampiro, eh? Pan comido comparado con Gozer.' Los extraños individuos comienzan a preparar sus equipos mientras intercambian bromas y comentarios sarcásticos.",
  final_ghostbusters: "Los autoproclamados 'Cazafantasmas' recorren el castillo con detectores que emiten pitidos cada vez más frenéticos. Finalmente localizan al Conde, quien parece confundido ante estos extraños intrusos. '¡Ahora, Egon!' grita uno de ellos, y disparan rayos de energía que atrapan al vampiro en un haz de luz. 'Venkman, la trampa!' Con un destello cegador y un alarido sobrenatural, el vampiro es succionado dentro de una pequeña caja metálica. 'Otro trabajo bien hecho, caballeros', comenta casualmente uno de ellos mientras te entregan una factura exorbitante. Abandonas el castillo junto a estos peculiares salvadores, preguntándote si todo esto no habrá sido una alucinación."
}

# FLAGS DEL JUEGO
# ==========================================
flags {
  es_de_noche: false,
  atacado_noche: false,
  conoce_vampiro: false,
  pasaje_descubierto: false,
  sarcofago_abierto: false,
  tiene_conocimiento: false,
  transformacion_iniciada: false,
  ha_bebido_copa: false,
  infectado: false,
  victoria: false,
  victoria_oscura: false,
  victoria_alianza: false,
  cortinas_descubiertas: false,
  oferta_vampiro: false,
  boton_descubierto: false,
  ghostbusters_llamados: false
}

# PROCESOS Y RESPUESTAS
# ==========================================

processes {
  # Controla el ciclo día/noche
  auto tiempo {
    every_turn {
      increment_counter("turnos")
      
      # Amanecer después de 15 turnos
      if counter("turnos") == 15 {
        set_flag("es_de_noche", false)
        message("amanecer")
      }
      
      # Anochecer después de 30 turnos
      if counter("turnos") == 30 {
        set_flag("es_de_noche", true)
        message("anochecer")
      }
      
      # Ataque nocturno
      if counter("turnos") == 35 && location == habitacion_invitados && !flag("atacado_noche") {
        set_flag("atacado_noche", true)
        message("ataque_nocturno")
        
        if carried(crucifijo) {
          message("crucifijo_salva")
        } else {
          message("sin_proteccion")
          end_game
        }
      }
      
      # Llegada de los Ghostbusters (5 turnos después de pulsar el botón)
      if flag("ghostbusters_llamados") {
        increment_counter("ghostbusters_timer")
        if counter("ghostbusters_timer") == 5 {
          message("llegada_ghostbusters")
          message("final_ghostbusters")
          end_game
        }
      }
      
      # Tiempo máximo para ganar
      if counter("turnos") >= 45 && !flag("victoria") && !flag("ghostbusters_llamados") {
        message("muerte_tiempo")
        end_game
      }
    }
  }
}

responses {
  # Inicio del juego
  auto inicio {
    on_first_turn {
      message("bienvenida")
    }
  }
  
  # Examinar objetos clave
  on "examinar espejo" {
    require: present(espejo_plata) && present(mayordomo)
    do: {
      message("reflejo_ausente")
      set_flag("conoce_vampiro", true)
      add_score(15)
      done
    }
  }
  
  on "examinar armadura" {
    require: present(armadura) && !carried(estaca)
    do: {
      message("encuentra_estaca")
      create(estaca, player)
      add_score(10)
      done
    }
  }
  
  on "examinar base armadura" {
    require: present(armadura) && !carried(martillo)
    do: {
      message("martillo_armadura")
      create(martillo, player)
      add_score(5)
      done
    }
  }
  
  # Leer el libro de vampiros
  on "leer libro vampiros" {
    require: carried(libro_vampiros)
    do: {
      message("libro_conocimiento")
      set_flag("tiene_conocimiento", true)
      add_score(10)
      done
    }
  }
  
  # Descubrir pasaje secreto
  on "usar mapa" {
    require: carried(mapa_castillo) && location == habitacion_conde && !flag("pasaje_descubierto")
    do: {
      message("encuentra_pasaje")
      set_flag("pasaje_descubierto", true)
      add_score(15)
      done
    }
  }
  
  # Examinar cortinas
  on "examinar cortinas" {
    require: location == cripta && present(cortinas_cripta) && !flag("cortinas_descubiertas")
    do: {
      message("descubrir_cortinas")
      set_flag("cortinas_descubiertas", true)
      add_score(5)
      done
    }
  }
  
  # Abrir el sarcófago
  on "abrir sarcofago" {
    require: location == cripta && present(sarcofago) && !flag("sarcofago_abierto") && !flag("es_de_noche")
    do: {
      message("abrir_sarcofago")
      set_flag("sarcofago_abierto", true)
      add_score(10)
      done
    }
  }
  
  # Oferta del vampiro después del ataque
  on "hablar vampiro" {
    require: flag("atacado_noche") && location == habitacion_invitados && !flag("oferta_vampiro")
    do: {
      message("oferta_vampiro")
      set_flag("oferta_vampiro", true)
      done
    }
  }
  
  # Intentar escapar
  on "escapar" {
    require: flag("conoce_vampiro") && !flag("es_de_noche")
    do: {
      message("intentar_escapar")
      message("escape_exitoso")
      add_score(15)
      end_game
      done
    }
  }
  
  on "huir" {
    require: flag("conoce_vampiro") && !flag("es_de_noche")
    do: {
      message("intentar_escapar")
      message("escape_exitoso")
      add_score(15)
      end_game
      done
    }
  }
  
  on "salir castillo" {
    require: flag("conoce_vampiro") && flag("es_de_noche")
    do: {
      message("intentar_escapar")
      message("escape_fallido")
      end_game
      done
    }
  }
  
  # Destruir al vampiro - Victoria clásica
  on "usar estaca en vampiro" {
    require: location == cripta && flag("sarcofago_abierto") && carried(estaca) && carried(martillo) && !flag("es_de_noche")
    do: {
      message("estaca_corazon")
      message("victoria")
      set_flag("victoria", true)
      add_score(35)
      end_game
      done
    }
  }
  
  on "clavar estaca" {
    require: location == cripta && flag("sarcofago_abierto") && carried(estaca) && carried(martillo) && !flag("es_de_noche")
    do: {
      message("estaca_corazon")
      message("victoria")
      set_flag("victoria", true)
      add_score(35)
      end_game
      done
    }
  }
  
  # Victoria alternativa: Decapitación
  on "atacar vampiro con cuchillo" {
    require: location == cripta && flag("sarcofago_abierto") && carried(cuchillo) && !flag("es_de_noche") && flag("tiene_conocimiento")
    do: {
      message("decapitacion_vampiro")
      message("victoria_decapitacion")
      set_flag("victoria", true)
      add_score(40)
      end_game
      done
    }
  }
  
  # Victoria alternativa: Exposición a la luz
  on "abrir cortinas" {
    require: location == cripta && flag("sarcofago_abierto") && !flag("es_de_noche") && flag("cortinas_descubiertas")
    do: {
      message("luz_solar_cripta")
      message("victoria_luz")
      set_flag("victoria", true)
      add_score(30)
      end_game
      done
    }
  }
  
  # Camino del vampirismo: Beber sangre
  on "beber sangre" {
    require: location == cripta && flag("sarcofago_abierto") && flag("es_de_noche")
    do: {
      message("beber_sangre_vampiro")
      set_flag("transformacion_iniciada", true)
      add_score(10)
      done
    }
  }
  
  on "beber de copa" {
    require: present(copa) && !flag("ha_bebido_copa")
    do: {
      message("beber_copa_sangre")
      set_flag("ha_bebido_copa", true)
      set_flag("infectado", true)
      add_score(5)
      done
    }
  }
  
  # Completar transformación vampírica
  on "dormir en sarcofago" {
    require: location == cripta && flag("transformacion_iniciada") && flag("es_de_noche")
    do: {
      message("dormir_sarcofago")
      message("final_vampiro")
      set_flag("victoria_oscura", true)
      add_score(25)
      end_game
      done
    }
  }
  
  # Alianza con el vampiro
  on "aceptar oferta" {
    require: flag("oferta_vampiro")
    do: {
      message("aceptar_pacto")
      message("final_alianza")
      set_flag("victoria_alianza", true)
      add_score(20)
      end_game
      done
    }
  }
}
```

## Finales Alternativos

La aventura "Sangre en la Penumbra" ofrece múltiples caminos y desenlaces, enriqueciendo la experiencia del jugador y aumentando su rejugabilidad:

### Victorias Heroicas

1. **Victoria Clásica (Estaca en el Corazón)**
   * El método tradicional: encontrar la estaca y el martillo, descubrir la cripta y destruir al vampiro durante el día.
   * Requiere: estaca, martillo, sarcófago abierto y que sea de día.
   * Recompensa: 35 puntos.

2. **Victoria por Decapitación**
   * Una alternativa menos conocida pero igualmente efectiva.
   * Requiere: cuchillo de cocina, conocimiento (del libro de vampiros), sarcófago abierto y que sea de día.
   * Recompensa: 40 puntos (mayor dificultad, mayor recompensa).

3. **Victoria por Luz Solar**
   * Descubrir las cortinas que ocultan una claraboya en la cripta.
   * Requiere: descubrir las cortinas, abrirlas mientras el sarcófago está abierto y es de día.
   * Recompensa: 30 puntos.

4. **Escape Exitoso**
   * Una victoria más modesta pero práctica: simplemente huir con vida del castillo.
   * Requiere: conocer la naturaleza del vampiro y escapar durante el día.
   * Recompensa: 15 puntos.

### Caminos Oscuros

1. **Transformación en Vampiro**
   * El jugador puede elegir convertirse en un vampiro bebiendo la sangre del Conde.
   * Requiere: beber la sangre del vampiro en la cripta y luego dormir en el sarcófago.
   * Recompensa: 25 puntos.

2. **Alianza con el Vampiro**
   * Tras sobrevivir al ataque nocturno, el vampiro puede ofrecer una alianza al jugador.
   * Requiere: hablar con el vampiro después del ataque y aceptar su oferta.
   * Recompensa: 20 puntos.

3. **Infección Gradual**
   * Comenzar una transformación lenta bebiendo de la copa en el comedor.
   * Este camino puede combinarse con otros para modificar sus desenlaces.
   * Recompensa inicial: 5 puntos.

### Finales Especiales

1. **Los Cazafantasmas al Rescate**
   * Un final secreto y cómico que rompe la cuarta pared.
   * Requiere: haber sobrevivido al ataque nocturno con el crucifijo, examinar la biblioteca (con un 40% de probabilidad de encontrar el botón secreto), y pulsar el botón con la inscripción "Who you gonna call?".
   * Esperar 5 turnos para que lleguen los Cazafantasmas y resuelvan la situación con su tecnología y humor característicos.
   * Sin recompensa de puntos (¡es una solución externa que no requiere habilidad!).

### Finales Trágicos

1. **Muerte por Ataque Nocturno**
   * Si el jugador no tiene el crucifijo durante el ataque en la habitación.

2. **Tiempo Agotado**
   * Si no se resuelve la aventura antes de que se acabe el tiempo disponible.

3. **Escape Fallido**
   * Intentar escapar durante la noche, cuando el vampiro está activo.

Estos múltiples caminos animan al jugador a explorar diferentes estrategias y descubrir todos los posibles desenlaces de la historia, aumentando significativamente el valor de rejuego de la aventura.

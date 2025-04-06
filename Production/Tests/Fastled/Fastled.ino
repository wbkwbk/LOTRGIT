#include "Confetti.h"
#include "BlendWave.h"
#include "RainbowMarch.h"
#include "Ripples.h"

Confetti confettiEffect;  // Erstelle ein Confetti-Objekt
BlendWave blendwaveEffect;  // Erstelle ein Objekt der BlendWave-Klasse
RainbowMarch rainbowEffect;  // Erstelle ein Objekt der RainbowMarch-Klasse
Ripples ripplesEffect;  // Erstelle ein Objekt der Ripples-Klasse

void setup() {
  //confettiEffect.setup();  // Setup der Confetti-Klasse
  //blendwaveEffect.setup();  // Setup der BlendWave-Klasse
  rainbowEffect.setup();  // Setup der RainbowMarch-Klasse
  //ripplesEffect.setup();  // Setup für die Ripples-Klasse  
  //ripplesEffect.startEffect();  // Starte den Ripple-Effekt
}

void loop() {
  //confettiEffect.loop();   // Loop der Confetti-Klasse
  //blendwaveEffect.loop();   // Loop der BlendWave-Klasse
  rainbowEffect.loop();   // Loop der RainbowMarch-Klasse
  //ripplesEffect.loop();   // Loop der Ripples-Klasse  
}


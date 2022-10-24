#include "FastLED.h"
#define NUM_LEDS 50
#define DATA_PIN 7
#define DEBUG false
#define PARTY_MODE true

// Allows us to reset the hardware clock
extern volatile unsigned long timer0_millis;

CRGB christmas_colors[ 4 ] = {
  CRGB::Navy,
  CRGB::OrangeRed,
  CRGB::Green,
  CRGB::Red
};

CRGB leds[NUM_LEDS];

String letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int lights[50] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 };
int letter_lights[26] = { 39, 38, 37, 36, 35, 34, 33, 32, 19, 20, 21, 22, 23, 24, 25, 26, 28, 15, 14, 13, 12, 11, 10, 9, 8, 7 };
bool timers[256];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2811, DATA_PIN, RGB>( leds, NUM_LEDS );
  FastLED.clear();
  FastLED.show();
}

void loop() {
  scene_transition();
  scene_separate_ways();
  
  scene_transition();
  message_happy_halloween();
  delay(2000);
  scene_run();

  scene_transition();
  message_bitchin();
  delay(2000);
  scene_intro();

  scene_transition();
  message_are_you_there_dustybun();
  delay(2000);
  scene_never_ending_story();

  scene_transition();
  message_chrissy_wake_up();
  delay(2000);
  scene_chrissy_wake_up();

  scene_transition();
  message_friends_dont_lie();
  delay(2000);
  scene_kids();

  //scene_theres_a_storm_coming();
  //scene_separate_ways();
}

void scene_transition() {
  fade_out_all();
  FastLED.show();
  FastLED.clear();
  delay(5000);

  if( PARTY_MODE ) {
    uint16_t random_delay = random16( 60 * 3 * 1000, 60 * 5 * 1000 );

    FastLED.setBrightness( 175 );
    set_colors( christmas_colors, 4 );
    FastLED.show();
    delay( random_delay );

    fade_out_all();
    FastLED.setBrightness( 255 );
    FastLED.show();
    FastLED.clear();
    delay(5000);
  }

  noInterrupts ();
  timer0_millis = 0;
  interrupts();
}

void scene_theres_a_storm_coming() {
  unsigned long start_time = adjusted_millis();
  unsigned long current_time = 0;
  unsigned long end_time = 135000;
  int index = 0;
  uint8_t chase_index = 0;
  int random = 0;
  int random_alt = 0;
  int bpm_primary = 400;
  int bpm_secondary = 100;
  int bpm_tertiary = 200;
  CRGB base_color = CRGB::Blue;
  CRGB primary_color = CRGB::Cyan;
  CRGB secondary_color = CRGB::Red;
  CRGB tertiary_color = CRGB::Purple;

  init_timers();
  fill_solid( &(leds[0]), NUM_LEDS, base_color );
  play_sound( "theres-a-storm-coming.mp3" );

  while ( current_time < end_time ) {
    if ( on_beat( bpm_primary ) ) {
      leds[chase_index] = blend( leds[chase_index], CRGB::Black, 64 );
    }

    if ( on_beat_secondary( bpm_secondary ) ) {
      leds[chase_index] = primary_color;
    }

    chase_index++;
    if ( chase_index > NUM_LEDS ) {
      chase_index = 0;
    }

    for ( index = 0; index < 15; index++ ) {
      random = random8( 0, NUM_LEDS );
      leds[random] = blend( leds[random], base_color, 1 );
    }

    FastLED.show();
    current_time = millis() - start_time;
    current_time = current_time - ( current_time * .02 );
  }
}

void scene_kids() {
  unsigned long start_time = adjusted_millis();
  unsigned long current_time = 0;
  unsigned long end_time = 158000;
  int index = 0;
  int random = 0;
  int random_alt = 0;
  int bpm_primary = 120;
  int bpm_secondary = 60;
  int bpm_tertiary = 240;
  CRGB base_color = CRGB::Blue;
  CRGB primary_color = CRGB::Green;
  CRGB secondary_color = CRGB::Red;
  CRGB tertiary_color = CRGB::Purple;

  init_timers();
  fill_solid( &(leds[0]), NUM_LEDS, base_color );
  play_sound( "kids.mp3" );

  while ( current_time < end_time ) {
    if (
        timer_between( 0, current_time, 16250 ) ||
        timer_between( 64250, current_time, 80250 )
      ) {
      if ( on_beat( bpm_primary ) ) {
        random = random8( 0, NUM_LEDS );
        leds[random] = primary_color;
      }
    }

    if (
        timer_between( 16250, current_time, 64250 ) ||
        timer_between( 80250, current_time, end_time )
      ) {
      if ( on_beat_secondary( bpm_secondary ) ) {
        random = random8( 0, NUM_LEDS );
        leds[random] = secondary_color;
      }
    }

    if (
        timer_between( 49000, current_time, 64250 ) ||
        timer_between( 137500, current_time, end_time )
      ) {
      if ( on_beat_tertiary( bpm_tertiary ) ) {
        random = random8( 0, NUM_LEDS );
        leds[random] = tertiary_color;
      }
    }

    for ( index = 0; index < 5; index++ ) {
      random = random8( 0, NUM_LEDS );
      leds[random] = blend( leds[random], base_color, 1 );
    }

    FastLED.show();
    current_time = millis() - start_time;
    current_time = current_time - ( current_time * .02 );
  }
}

void scene_run() {
  play_sound( "run.mp3" );
  delay(7500);
  
  display_letter( "R", 2500 );
  delay(2100);
  display_letter( "I", 900 );
  delay(1000);
  display_letter( "G", 800 );
  delay(400);
  display_letter( "H", 800 );
  delay(400);
  display_letter( "T", 800 );
  delay(800);

  display_letter( "H", 600 );
  delay(600);
  display_letter( "E", 600 );
  delay(400);
  display_letter( "R", 600 );
  delay(600);
  display_letter( "E", 600 );
  delay(13000);

  display_letter( "R", 800 );
  delay(1200);
  display_letter( "U", 800 );
  delay(2400);
  display_letter( "N", 800 );
  delay(3000);

  set_colors( christmas_colors, 4 );

  flicker( 14000, 255, 100 );
}

void scene_intro() {
  CRGB color = CRGB::Red;

  play_sound( "intro.mp3" );
  delay(5400);
  fill_solid( &(leds[0]), NUM_LEDS, color );
  flicker( 60000, 32, 100 );
}

void scene_chrissy_wake_up() {
  play_sound( "chrissy-wake-up.mp3" );
  delay(2400);
  
  display_word( "CHRISY", 600 );
  display_word( "WAKE", 300 );
  display_word( "UP", 600 );

  delay(500);

  display_word( "I", 300 );
  display_word( "DONT", 500 );
  display_word( "LIKE", 400 );
  display_word( "THIS", 400 );

  delay(300);

  display_word( "CHRISY", 600 );
  display_word( "WAKE", 300 );
  display_word( "UP", 800 );

  delay(1000);

  display_word( "HEY", 400 );
  display_word( "HELLO", 800 );

  delay(200);

  christmas_color_walk( 2800 );

  delay(400);

  display_word( "I", 200 );
  display_word( "DONT", 300 );
  display_word( "LIKE", 500 );
  display_word( "THIS", 500 );
  display_word( "CHRISY", 600 );
  display_word( "WAKE", 200 );
  display_word( "UP", 800 );

  delay(800);

  set_colors( christmas_colors, 4 );
  flicker( 400, 255, 128 );
  fade_out_all();

  christmas_color_walk( 19000 );

  set_colors( christmas_colors, 4 );
  flicker( 1600, 128, 128 );
  fade_out_all();

  display_word( "CHRISY", 600 );
  display_word( "WAKE", 300 );
  display_word( "UP", 600 );

  delay(500);

  display_word( "I", 300 );
  display_word( "DONT", 500 );
  display_word( "LIKE", 400 );
  display_word( "THIS", 400 );

  delay(300);

  display_word( "CHRISY", 600 );
  display_word( "WAKE", 300 );
  display_word( "UP", 800 );

  delay(1000);

  display_word( "HEY", 400 );
  display_word( "HELLO", 800 );

  delay(200);

  christmas_color_walk(2200);

  delay(400);

  display_word( "I", 300 );
  display_word( "DONT", 400 );
  display_word( "LIKE", 400 );
  display_word( "THIS", 400 );
  display_word( "CHRISY", 600 );

  delay(300);

  display_word( "JESUS", 500 );
  display_word( "H", 400 );
  display_word( "CHRISY", 600 );

  delay(300);

  display_word( "I", 300 );
  display_word( "DONT", 200 );
  display_word( "LIKE", 500 );
  display_word( "THIS", 300 );
  display_word( "CHRISY", 600 );
  display_word( "WAKE", 300 );
  display_word( "UP", 800 );  

  delay(800);

  set_colors( christmas_colors, 4 );
  flicker( 800, 255, 128 );
}

void scene_never_ending_story() {
  unsigned long start_time = adjusted_millis();
  unsigned long current_time = 0;
  unsigned long end_time = 85000;
  uint8_t hue = 0;
  uint8_t hue_increase = 0;
  uint8_t brightness_decrease = 0;
  int bpm = 0;

  init_timers();
  FastLED.setBrightness(0);
  fill_rainbow( &(leds[0]), NUM_LEDS, hue );
  play_sound( "never-ending-story.mp3" );

  while ( current_time < end_time ) {
    if ( timer_once( 0, current_time, 18500 ) ) {
      FastLED.setBrightness( 50 );
    }

    if ( timer_once( 1, current_time, 21750 ) ) {
      FastLED.setBrightness( 100 );
    }

    if ( timer_once( 2, current_time, 35500 ) ) {
      FastLED.setBrightness( 255 );
    }

    if ( current_time < 35500 ) {
      hue_increase = 2;
      bpm = 272;
    } else if ( current_time < 35500 ) {
      hue_increase = 6;
    } else {
      hue_increase = 12;
      bpm = 136;    
      brightness_decrease = beatsin8( 136, 0, 64 );

      FastLED.setBrightness( 255 - brightness_decrease );
    }

    if ( on_beat( bpm ) ) {
      hue = hue + hue_increase;
      fill_rainbow( &(leds[0]), NUM_LEDS, hue );
    }

    FastLED.show();
    current_time = millis() - start_time;
    current_time = current_time - ( current_time * .02 );
  }
}

void scene_separate_ways() {
  unsigned long start_time = adjusted_millis();
  unsigned long current_time = 0;
  unsigned long end_time = 200000;
  int num_colors = 5;
  int index = 0;
  static uint8_t beat_index = 0;
  uint8_t brightness = 0;
  uint8_t min_brightness = 32;

  CRGB colors[ num_colors ] = {
    CRGB::Indigo,
    CRGB::Purple,
    CRGB::OrangeRed,
    CRGB::DeepPink,
    CRGB::DarkBlue,
  };

  init_timers();
  FastLED.setBrightness( 0 );
  set_colors( colors, num_colors );
  play_sound( "separate-ways.mp3" );

  while ( current_time < end_time ) {
    // soft bass
    separate_ways_beat( 0, current_time, 3900, 200, colors, num_colors );
    separate_ways_beat( 1, current_time, 11200, 200, colors, num_colors );
    separate_ways_beat( 2, current_time, 18600, 200, colors, num_colors );
    separate_ways_beat( 3, current_time, 26000, 200, colors, num_colors );
    separate_ways_beat( 4, current_time, 33400, 200, colors, num_colors );
    separate_ways_beat( 5, current_time, 40800, 200, colors, num_colors );
    separate_ways_beat( 6, current_time, 48000, 200, colors, num_colors );

    // heartbeat
    separate_ways_beat( 7, current_time, 49000, 200, colors, num_colors );
    separate_ways_beat( 8, current_time, 49200, 200, colors, num_colors );
    separate_ways_beat( 9, current_time, 50000, 200, colors, num_colors );
    separate_ways_beat( 10, current_time, 50800, 200, colors, num_colors );
    separate_ways_beat( 11, current_time, 51000, 200, colors, num_colors );
    separate_ways_beat( 12, current_time, 51800, 200, colors, num_colors );
    separate_ways_beat( 13, current_time, 52800, 200, colors, num_colors );
    separate_ways_beat( 14, current_time, 53000, 200, colors, num_colors );
    separate_ways_beat( 15, current_time, 53500, 200, colors, num_colors );
    separate_ways_beat( 16, current_time, 54400, 200, colors, num_colors );
    separate_ways_beat( 17, current_time, 54600, 200, colors, num_colors );
    separate_ways_beat( 18, current_time, 55500, 200, colors, num_colors );
    separate_ways_beat( 19, current_time, 56400, 200, colors, num_colors );

    separate_ways_beat( 20, current_time, 56600, 200, colors, num_colors );
    separate_ways_beat( 21, current_time, 57400, 200, colors, num_colors );
    separate_ways_beat( 22, current_time, 58200, 200, colors, num_colors );
    separate_ways_beat( 23, current_time, 58400, 200, colors, num_colors );
    separate_ways_beat( 24, current_time, 59200, 200, colors, num_colors );
    separate_ways_beat( 25, current_time, 60000, 200, colors, num_colors );
    separate_ways_beat( 26, current_time, 60200, 200, colors, num_colors );

    // fast buildup
    separate_ways_beat( 27, current_time, 61000, 200, colors, num_colors );
    separate_ways_beat( 28, current_time, 61200, 200, colors, num_colors );
    separate_ways_beat( 29, current_time, 61400, 200, colors, num_colors );
    separate_ways_beat( 30, current_time, 61600, 200, colors, num_colors );
    separate_ways_beat( 31, current_time, 61800, 200, colors, num_colors );
    separate_ways_beat( 32, current_time, 62000, 200, colors, num_colors );
    separate_ways_beat( 33, current_time, 62200, 200, colors, num_colors );
    separate_ways_beat( 34, current_time, 62400, 200, colors, num_colors );
    separate_ways_beat( 35, current_time, 62600, 200, colors, num_colors );
    separate_ways_beat( 36, current_time, 62800, 200, colors, num_colors );
    separate_ways_beat( 37, current_time, 63000, 200, colors, num_colors );
    separate_ways_beat( 38, current_time, 63200, 200, colors, num_colors );
    separate_ways_beat( 39, current_time, 63400, 200, colors, num_colors );
    separate_ways_beat( 40, current_time, 63600, 200, colors, num_colors );
    separate_ways_beat( 41, current_time, 63800, 200, colors, num_colors );
    separate_ways_beat( 42, current_time, 64000, 200, colors, num_colors );
    separate_ways_beat( 43, current_time, 64200, 200, colors, num_colors );
    separate_ways_beat( 44, current_time, 64400, 200, colors, num_colors );

    // long
    separate_ways_beat( 45, current_time, 64600, 255, colors, num_colors );

    separate_ways_beat( 46, current_time, 70300, 200, colors, num_colors );
    separate_ways_beat( 47, current_time, 70800, 200, colors, num_colors );
    
    // long
    separate_ways_beat( 48, current_time, 71200, 200, colors, num_colors );

    separate_ways_beat( 49, current_time, 76800, 200, colors, num_colors );
    separate_ways_beat( 50, current_time, 77100, 200, colors, num_colors );
    separate_ways_beat( 51, current_time, 77400, 200, colors, num_colors );

    // long
    separate_ways_beat( 52, current_time, 77700, 255, colors, num_colors ); 
   
    // buildup
    separate_ways_beat( 53, current_time, 81400, 200, colors, num_colors );
    separate_ways_beat( 54, current_time, 82100, 200, colors, num_colors );
    separate_ways_beat( 55, current_time, 82500, 200, colors, num_colors );
    separate_ways_beat( 56, current_time, 83000, 200, colors, num_colors );
    separate_ways_beat( 57, current_time, 83400, 200, colors, num_colors );
    separate_ways_beat( 58, current_time, 83700, 200, colors, num_colors );
    separate_ways_beat( 59, current_time, 84300, 200, colors, num_colors );
    separate_ways_beat( 60, current_time, 84600, 200, colors, num_colors );

    // fast run
    separate_ways_beat( 61, current_time, 85000, 200, colors, num_colors );
    separate_ways_beat( 62, current_time, 85250, 200, colors, num_colors );
    separate_ways_beat( 63, current_time, 85500, 200, colors, num_colors );
    separate_ways_beat( 64, current_time, 85750, 200, colors, num_colors );
    separate_ways_beat( 65, current_time, 86000, 200, colors, num_colors );

    // big hit - big build up
    separate_ways_beat( 66, current_time, 88800, 255, colors, num_colors );

    // soft bass
    separate_ways_beat( 67, current_time, 92500, 200, colors, num_colors );
    separate_ways_beat( 68, current_time, 100000, 200, colors, num_colors );
    separate_ways_beat( 69, current_time, 105500, 150, colors, num_colors );
    //
    //

    // three hit build - 'If you Must Gooooo'
    separate_ways_beat( 70, current_time, 119300, 200, colors, num_colors );
    separate_ways_beat( 71, current_time, 119600, 200, colors, num_colors );
    separate_ways_beat( 72, current_time, 119900, 200, colors, num_colors );

    // heartbeat
    separate_ways_beat( 73, current_time, 121000, 200, colors, num_colors );
    separate_ways_beat( 74, current_time, 121200, 200, colors, num_colors );
    separate_ways_beat( 75, current_time, 122000, 200, colors, num_colors );
    separate_ways_beat( 76, current_time, 122800, 200, colors, num_colors );
    separate_ways_beat( 77, current_time, 123000, 200, colors, num_colors );
    separate_ways_beat( 78, current_time, 124000, 200, colors, num_colors );
    separate_ways_beat( 79, current_time, 124800, 200, colors, num_colors );
    separate_ways_beat( 80, current_time, 125000, 200, colors, num_colors );

    // skip heartbeat
    separate_ways_beat( 81, current_time, 125500, 200, colors, num_colors );
    separate_ways_beat( 82, current_time, 126000, 200, colors, num_colors );
    separate_ways_beat( 83, current_time, 126250, 200, colors, num_colors );
    separate_ways_beat( 84, current_time, 127000, 200, colors, num_colors );

    // heartbeat
    separate_ways_beat( 85, current_time, 127500, 200, colors, num_colors );
    separate_ways_beat( 86, current_time, 128300, 200, colors, num_colors );
    separate_ways_beat( 87, current_time, 128500, 200, colors, num_colors );
    separate_ways_beat( 88, current_time, 129500, 200, colors, num_colors );
    separate_ways_beat( 89, current_time, 130300, 200, colors, num_colors );
    separate_ways_beat( 90, current_time, 130500, 200, colors, num_colors );
    separate_ways_beat( 91, current_time, 131300, 200, colors, num_colors );

    // fast buildup
    separate_ways_beat( 92, current_time, 125000, 200, colors, num_colors );
    separate_ways_beat( 93, current_time, 125200, 200, colors, num_colors );
    separate_ways_beat( 94, current_time, 125400, 200, colors, num_colors );
    separate_ways_beat( 95, current_time, 125600, 200, colors, num_colors );
    separate_ways_beat( 96, current_time, 125800, 200, colors, num_colors );
    separate_ways_beat( 97, current_time, 126000, 200, colors, num_colors );
    separate_ways_beat( 98, current_time, 126200, 200, colors, num_colors );
    separate_ways_beat( 99, current_time, 126400, 200, colors, num_colors );
    separate_ways_beat( 100, current_time, 126600, 200, colors, num_colors );
    separate_ways_beat( 101, current_time, 126800, 200, colors, num_colors );
    separate_ways_beat( 102, current_time, 127000, 200, colors, num_colors );
    separate_ways_beat( 103, current_time, 127200, 200, colors, num_colors );
    separate_ways_beat( 104, current_time, 127400, 200, colors, num_colors );
    separate_ways_beat( 105, current_time, 127600, 200, colors, num_colors );
    separate_ways_beat( 106, current_time, 127800, 200, colors, num_colors );
    separate_ways_beat( 107, current_time, 128000, 200, colors, num_colors );
    separate_ways_beat( 108, current_time, 128200, 200, colors, num_colors );
    separate_ways_beat( 109, current_time, 128400, 200, colors, num_colors );

    for ( int i = 0; i < 2; i++ ) {
      index = random8( 0, NUM_LEDS );
      leds[index].fadeToBlackBy( 1 );      
    }      

    if ( on_beat( 130 ) ) {
      leds[beat_index] = get_color( beat_index, colors, num_colors );
      beat_index++;

      if ( beat_index > NUM_LEDS ) {
        beat_index = 0;
      }
    }

    FastLED.show();
    current_time = millis() - start_time;
    current_time = current_time - ( current_time * .02 );
  }
}

void separate_ways_beat( int timer_key, unsigned long current_time, unsigned long trigger_time, uint8_t brightness, CRGB colors[], int num_colors ) {
  if ( current_time > trigger_time & !timers[timer_key] ) {
    int prev_timer_key = timer_key - 1;

    if ( prev_timer_key > -1 ) {
      timers[prev_timer_key] = true;
    }

    if ( current_time < trigger_time + 50 ) {
      set_colors( colors, num_colors );
      FastLED.setBrightness( brightness );
    } else {
      brightness = beatsin8( 16, 64, brightness, trigger_time, brightness * .75 );
      FastLED.setBrightness( brightness );
    }

    if ( brightness <= 64 ) {
      timers[timer_key] = true;
    }
  }
}

bool on_beat( int bpm ) {
  int beat = beatsin8( bpm / 2, 0, 1 );
  static int last_beat = 1;
  bool hit_beat = false;

  if( beat != last_beat ) {
    last_beat = beat;
    hit_beat = true;
  } else {
    hit_beat = false;
  }

  return hit_beat;
}

bool on_beat_secondary( int bpm ) {
  int beat = beatsin8( bpm / 2, 0, 1 );
  static int last_beat = 1;
  bool hit_beat = false;

  if( beat != last_beat ) {
    last_beat = beat;
    hit_beat = true;
  } else {
    hit_beat = false;
  }

  return hit_beat;
}

bool on_beat_tertiary( int bpm ) {
  int beat = beatsin8( bpm / 2, 0, 1 );
  static int last_beat = 1;
  bool hit_beat = false;

  if( beat != last_beat ) {
    last_beat = beat;
    hit_beat = true;
  } else {
    hit_beat = false;
  }

  return hit_beat;
}

unsigned long adjusted_millis() {
  // millis appears to be fast by approx 2%
  unsigned long ms = millis();
  return ms - ( ms * .019 );
}

int scale_brightness( uint8_t brightness ) {
  int brightness_scale[28] = { 100, 60, 40, 30, 25, 22.5, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  static int step = 0;

  if ( step == 28 ) {
    step = 0;
  } else {
    brightness = brightness * brightness_scale[step];
    step++;
  }

  return brightness;  
}

bool timer_once( int timer_key, unsigned long current_time, unsigned long trigger_time ) {
  bool trigger = false;

  if ( ( current_time > trigger_time ) && ! timers[timer_key] ) {
    trigger = true;
    timers[timer_key] = true;
  }

  return trigger;
}

bool timer_between( unsigned long start_time, unsigned long current_time, unsigned long end_time ) {
  bool trigger = false;

  if ( current_time > start_time && current_time < end_time ) {
    trigger = true;
  }

  return trigger;
};

void init_timers() {
  for( int i = 0; i < 99; i++ ) {
    timers[i] = false;
  }
}

void christmas_color_walk( unsigned long duration ) {
  set_colors( christmas_colors, 4 );
  unsigned long start = millis();

  while( millis() < start + duration ) {
    for( int j = 0; j < 4; j++ ) {
      for( int i = 0; i < NUM_LEDS; i++ ) {
        leds[i] = get_color( i + j, christmas_colors, 4 );
        FastLED.show();      
      }

      delay(200);
    }
  }

  fade_out_all();
}

void set_colors( CRGB colors[], int num_colors ) {
  for( int i = 0; i < NUM_LEDS; i++ ) {
    leds[i] = get_color( i, colors, num_colors );
  }
}

CRGB get_color( int index, CRGB colors[], int num_colors ) {
  return colors[ index % num_colors ];
}

void fade_out_all() {
  for( int j = 0; j < 26; j++ ) {
    for( int i = 0; i < NUM_LEDS; i++ ) {
      leds[i] = blend( leds[i], CRGB::Black, 37 );
    }
    delay(10);
    FastLED.show();
  }
}

void christmas_fade_in( int index ) {
  CRGB color = get_color( index, christmas_colors, 4 );
  fade_to( index, color );
}

void fade_out( int index ) {
  fade_to( index, CRGB::Black );
}

void fade_to( int index, CRGB color ) {
  for( int i = 1; i < 26; i++ ) {
    leds[index] = blend( leds[index], color, 10 );
    FastLED.show();
  }
  leds[index] = color;
  FastLED.show();
}

void display_message( String message, int duration, int pause_duration, bool sound ) {
  int length = message.length() + 1;
  char characters[ length ];
  message.toCharArray( characters, length );

  fade_out_all();
  delay( pause_duration );

  for( int i = 0; i < length - 1; i++ ) {
    if ( ' ' == characters[i] ) {
      delay( duration );          
    } else {
      if( sound ) {
        play_light_sound();
      }
      display_letter( String( characters[i] ), duration );
    }

    delay( pause_duration );
  }
}

void display_word( String word, unsigned long duration ) {
  int length = word.length() + 1;
  char characters[ length ];
  word.toCharArray( characters, length );

  for( int i = 0; i < length - 1; i++ ) {
    int letter_index = letters.indexOf( word[i] );
    int led_index = letter_lights[letter_index];

    leds[led_index] = get_color( led_index, christmas_colors, 4 );
  }

  FastLED.show();
  delay( duration );

  for( int i = 0; i < length - 1; i++ ) {
    int letter_index = letters.indexOf( word[i] );
    int led_index = letter_lights[letter_index];

    leds[led_index] = CRGB::Black;
  }

  FastLED.show();
}

void display_letter( String letter, int duration ) {
  int letter_index = letters.indexOf( letter );
  int led_index = letter_lights[letter_index];

  christmas_fade_in( led_index );
  delay( duration );
  fade_out( led_index );
}

void flicker( unsigned long duration, int max_flicker, int max_delay ) {
  unsigned long start = millis();

  while( millis() < start + duration ) {
    int random_bright = random8( 0, max_flicker );
    int random_delay = random8( 10, max_delay );
    int random_full_light = random8( 0, 2 );

    for( int i = 0; i < NUM_LEDS; i++ ) {
      if ( 0 == random_full_light ) {
        leds[i].maximizeBrightness();
      }
      leds[i].fadeLightBy( random_bright );
    }

    FastLED.show();
    delay( random_delay );
  }
}

void message_chrissy_wake_up() {
  display_message( "CHRISSY WAKE UP", 500, 300, true );
}

void message_happy_halloween() {
  display_message( "HAPPY HALLOWEEN", 500, 300, true );
}

void message_bitchin() {
  display_message( "BITCHIN", 500, 300, true );
}

void message_are_you_there_dustybun() {
  display_message( "ARE YOU THERE DUSTYBUN", 500, 300, true );
}

void message_friends_dont_lie() {
  display_message( "HAPPY HALLOWEEN", 500, 300, true );
}

void message_alphabet() {
  display_message( "AAABBBCCCDDDEEEFFFGGGHHHIIIJJJKKKLLLMMMNNNOOOPPPQQQRRRSSSTTTUUUVVVXXXYYYZZZ", 500, 300, true );
}

void demo_colors_on_off() {
  for( int i = 0; i < NUM_LEDS; i++ ) {
    christmas_fade_in(i);    
  }
  
  for( int i = 0; i < NUM_LEDS; i++ ) {
    fade_out(i);    
  }  
}

void demo_chase() {
  static uint8_t hue = 0;

  for( int i = 0; i < NUM_LEDS; i++ ) {
    hue++;
    leds[i] = CHSV( hue, 220, 255 );

    for( int j = 1; j < NUM_LEDS; j++ ) {
      int brightness = j * ( 255 / ( NUM_LEDS * 5 ) );
      leds[ utility_wrap_index( i - j ) ].fadeLightBy( brightness );
    }
    FastLED.show();
    delay(30);
  }
}

void demo_fill_rainbow() {
  fill_rainbow( &(leds[0]), NUM_LEDS, 0 );
  FastLED.show();
}

void millis_test() {
  unsigned long start_time = millis();
  unsigned long end_time = 200000;
  unsigned long current_time = 0;

  init_timers();
  play_sound( "metronome.mp3" );
  
  while ( current_time < end_time ) {
    millis_test_step( 0, current_time );
    millis_test_step( 1, current_time );
    millis_test_step( 2, current_time );
    millis_test_step( 3, current_time );
    millis_test_step( 4, current_time );
    millis_test_step( 5, current_time );
    millis_test_step( 6, current_time );
    millis_test_step( 7, current_time );
    millis_test_step( 8, current_time );
    millis_test_step( 9, current_time );
    millis_test_step( 10, current_time );
    millis_test_step( 11, current_time );
    millis_test_step( 12, current_time );
    millis_test_step( 13, current_time );
    millis_test_step( 14, current_time );
    millis_test_step( 15, current_time );
    millis_test_step( 16, current_time );
    millis_test_step( 17, current_time );
    millis_test_step( 18, current_time );
    millis_test_step( 19, current_time );
    millis_test_step( 20, current_time );
    millis_test_step( 21, current_time );
    millis_test_step( 22, current_time );
    millis_test_step( 23, current_time );
    millis_test_step( 24, current_time );
    millis_test_step( 25, current_time );
    millis_test_step( 26, current_time );
    millis_test_step( 27, current_time );
    millis_test_step( 28, current_time );
    millis_test_step( 29, current_time );
    millis_test_step( 30, current_time );
    millis_test_step( 31, current_time );
    millis_test_step( 32, current_time );
    millis_test_step( 33, current_time );
    millis_test_step( 34, current_time );
    millis_test_step( 35, current_time );
    millis_test_step( 36, current_time );
    millis_test_step( 37, current_time );
    millis_test_step( 38, current_time );
    millis_test_step( 39, current_time );
    millis_test_step( 40, current_time );
    millis_test_step( 41, current_time );
    millis_test_step( 42, current_time );
    millis_test_step( 43, current_time );
    millis_test_step( 44, current_time );
    millis_test_step( 45, current_time );
    millis_test_step( 46, current_time );
    millis_test_step( 47, current_time );
    millis_test_step( 48, current_time );
    millis_test_step( 49, current_time );
    millis_test_step( 50, current_time );
    
    FastLED.show();
    current_time = millis() - start_time;
    current_time = current_time - ( current_time * .02 );
  }  
}

void millis_test_step( int index, unsigned long current_time ) {
  unsigned long trigger_time = ( (long)index * 1000 ) + 50;

  if ( timer_once( index, current_time, trigger_time ) ) {
    leds[index] = CRGB::Blue;
  }
}

int utility_wrap_index( int num ) {
  if( num < 0  ) {
    num = NUM_LEDS + num;
  }

  return num;
}

void utility_shuffle( int *array, size_t n ) {
  if ( n > 1 ) {
    size_t i;

    for ( i = 0; i < n - 1; i++ ) {
      size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
      int t = array[j];
      array[j] = array[i];
      array[i] = t;
    }
  }
}

void utility_debug( String message ) {
  if ( DEBUG ) {
    Serial.println( message );
  }
}

void utility_debug( int message ) {
  if ( DEBUG ) {
    Serial.println( message );
  }
}

void utility_debug( unsigned long message ) {
  if ( DEBUG ) {
    Serial.println( message );
  }
}

void utility_debug( uint8_t message ) {
  if ( DEBUG ) {
    Serial.println( message );
  }
}

void play_sound( String sound ) {
  if ( ! DEBUG ) {
    Serial.println( sound );
  }
}

void play_light_sound() {
  char sound[12];  
  int random_number = random8( 1, 5 );

  sprintf( sound, "light-%d.mp3", random_number );

  play_sound( sound );  
}
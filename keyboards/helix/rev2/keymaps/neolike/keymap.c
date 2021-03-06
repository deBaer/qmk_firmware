#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _LAYER1 = 0,
    _LAYER2LEFTSHIFT = 1,
    _LAYER2RIGHTSHIFT = 2,
    _LAYER3 = 3,
    _LAYER4 = 4,
    _LAYER5 = 5,
    _LAYER6 = 6
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  EISU,
  KANA,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5,
                 KC_6, KC_7, KC_8, KC_9, KC_0, KC_NO,
                 KC_TAB, KC_X, KC_V, KC_L, KC_C, KC_W,
                 KC_K, KC_H, KC_G, KC_F, KC_Q, MO(3),
                 MO(3), KC_U, KC_I, KC_A, KC_E, KC_O,
                 KC_S, KC_N, KC_R, KC_T, KC_D, KC_Y,
                 MO(1), UC(0xFC), UC(0xF6), UC(0xE4), KC_P, KC_Z, KC_NO,
                 KC_N, KC_B, KC_M, KC_COMM, KC_DOT, KC_J, MO(2),
                 KC_LCTL, KC_LALT, MO(4), KC_LEFT, KC_RGHT, KC_BSPC, KC_DEL,
                 KC_ENT, KC_SPC, KC_UP, KC_DOWN, UC(0xDF), KC_RGUI, KC_RALT),

    [1] = LAYOUT(LSFT(KC_ESC), UC(0xB0), UC(0xA7), UC(0x2113), UC(0xBB), UC(0xAB),
                 KC_DLR, UC(0x20AC), UC(0x201E), UC(0x201C), UC(0x201D), KC_NO,
                 LSFT(KC_TAB), LSFT(KC_X), LSFT(KC_V), LSFT(KC_L), LSFT(KC_C), LSFT(KC_W),
                 LSFT(KC_K), LSFT(KC_H), LSFT(KC_G), LSFT(KC_F), LSFT(KC_Q), MO(5),
                 MO(5), LSFT(KC_U), LSFT(KC_I), LSFT(KC_A), LSFT(KC_E), LSFT(KC_O),
                 LSFT(KC_S), LSFT(KC_N), LSFT(KC_R), LSFT(KC_T), LSFT(KC_D), LSFT(KC_Y),
                 KC_NO, UC(0xDC), UC(0xD6), UC(0xC4), LSFT(KC_P), LSFT(KC_Z), KC_NO,
                 LSFT(KC_N), LSFT(KC_B), LSFT(KC_M), UC(0x2013), UC(0x2022), LSFT(KC_J), KC_CAPS,
                 LSFT(KC_LCTL), LSFT(KC_LALT), KC_NO, LSFT(KC_LEFT), LSFT(KC_RGHT), LSFT(KC_BSPC), LSFT(KC_DEL),
                 LSFT(KC_ENT), LSFT(KC_SPC), LSFT(KC_UP), LSFT(KC_DOWN), UC(0x1E9E), LSFT(KC_RGUI), LSFT(KC_RALT)),

    [2] = LAYOUT(RSFT(KC_ESC), UC(0xB0), UC(0xA7), UC(0x2113), UC(0xBB), UC(0xAB),
                 RSFT(KC_4), UC(0x20AC), UC(0x201E), UC(0x201C), UC(0x201D), KC_NO,
                 RSFT(KC_TAB), RSFT(KC_X), RSFT(KC_V), RSFT(KC_L), RSFT(KC_C), RSFT(KC_W),
                 RSFT(KC_K), RSFT(KC_H), RSFT(KC_G), RSFT(KC_F), RSFT(KC_Q), MO(5),
                 MO(5), RSFT(KC_U), RSFT(KC_I), RSFT(KC_A), RSFT(KC_E), RSFT(KC_O),
                 RSFT(KC_S), RSFT(KC_N), RSFT(KC_R), RSFT(KC_T), RSFT(KC_D), RSFT(KC_Y),
                 KC_CAPS, UC(0xDC), UC(0xD6), UC(0xC4), RSFT(KC_P), RSFT(KC_Z), KC_NO,
                 RSFT(KC_N), RSFT(KC_B), RSFT(KC_M), UC(0x2013), UC(0x2022), RSFT(KC_J), KC_NO,
                 RSFT(KC_LCTL), RSFT(KC_LALT), KC_NO, RSFT(KC_LEFT), RSFT(KC_RGHT), RSFT(KC_BSPC), RSFT(KC_DEL),
                 RSFT(KC_ENT), RSFT(KC_SPC), RSFT(KC_UP), RSFT(KC_DOWN), UC(0x1E9E), RSFT(KC_RGUI), RSFT(KC_RALT)),

    [3] = LAYOUT(KC_ESC, UC(0xB9), UC(0xB2), UC(0xB3), UC(0x203A), UC(0x2039),
                 UC(0xA2), UC(0xA5), UC(0x201A), UC(0x2018), UC(0x2019), KC_NO,
                 KC_TAB, UC(0x2026), KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC,
                 KC_EXLM, KC_LT, KC_GT, KC_EQL, KC_AMPR, KC_NO,
                 KC_NO, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,
                 KC_QUES, KC_LPRN, KC_RPRN, KC_MINS, KC_COLN, KC_AT,
                 MO(5), KC_HASH, KC_DLR, KC_PIPE, KC_TILD, KC_GRV, KC_NO,
                 KC_NO, KC_PLUS, KC_PERC, KC_DQUO, KC_QUOT, KC_SCLN, MO(5),
                 KC_LCTL, KC_LALT, MO(6), KC_NO, KC_NO, KC_HOME, KC_END,
                 KC_PGUP, KC_PGDN, KC_NO, KC_NO, UC(0x17F), KC_RGUI, KC_RALT),
    
    [4] = LAYOUT(KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
                 KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_P7, KC_P8, KC_P9, KC_PPLS, MO(6),
                 MO(6), KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_P4, KC_P5, KC_P6, KC_PCMM, KC_PDOT,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_P1, KC_P2, KC_P3, KC_PGUP, KC_NO,
                 KC_LCTL, KC_LALT, KC_NO, KC_LEFT, KC_RGHT, KC_BSPC, KC_DEL,
                 KC_NO, KC_P0, KC_UP, KC_DOWN, KC_NO, KC_RGUI, KC_RALT),
    
    [5] = LAYOUT(RGB_TOG, RGB_MOD, RGB_RMOD, RGB_HUI, RGB_HUD, RGB_SAI,
                 RGB_SAD, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, RGB_M_P,
                 KC_NO, UC_M_LN, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, KC_NO,
                 KC_NO, UC_M_MA, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_MS_R,
                 KC_NO, UC_M_WC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_ACL0, KC_ACL1, KC_ACL1, KC_BTN3, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
    
    [6] = LAYOUT(RGB_TOG, RGB_MOD, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                 KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO)

};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
          //rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  } */
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static const char helix_logo[] PROGMEM ={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write_P(matrix, helix_logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static void render_rgbled_status(bool full, struct CharacterMatrix *matrix) {
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
      if (full) {
          snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
                   rgblight_config.mode,
                   rgblight_config.hue/RGBLIGHT_HUE_STEP,
                   rgblight_config.sat/RGBLIGHT_SAT_STEP,
                   rgblight_config.val/RGBLIGHT_VAL_STEP);
      } else {
          snprintf(buf, sizeof(buf), "[%2d] ",rgblight_config.mode);
      }
      matrix_write(matrix, buf);
  }
#endif
}

static void render_layer_status(struct CharacterMatrix *matrix) {
  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[10];
  matrix_write_P(matrix, PSTR("Layer: "));
    switch (layer_state) {
        case 0:
           matrix_write_P(matrix, PSTR("1"));
           break;
        case 4:
           matrix_write_P(matrix, PSTR("2 R"));
           break;
        case 2:
           matrix_write_P(matrix, PSTR("2 L"));
           break;
        case 8:
           matrix_write_P(matrix, PSTR("3"));
           break;
        case 16:
           matrix_write_P(matrix, PSTR("4"));
           break;
        case 34:
        case 36:
        case 40:
           matrix_write_P(matrix, PSTR("5"));
           break;
        case 72:
        case 80:
           matrix_write_P(matrix, PSTR("6"));
           break;
        default:
           matrix_write_P(matrix, PSTR("Undef-"));
           snprintf(buf,sizeof(buf), "%ld", layer_state);
           matrix_write(matrix, buf);
    }
}

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
    static const char os_logo[][2][3] PROGMEM  ={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}},{{0x99,0xa0,0},{0xb9,0xba,0}},{{0x3f,0x3f,0},{0x3f,0x3f,0}}};
  if(unicode_config.input_mode==UC_MAC){
    matrix_write_P(matrix, os_logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[0][1]);
  }else if(unicode_config.input_mode==UC_WINC){
    matrix_write_P(matrix, os_logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write_P(matrix, os_logo[1][1]);
  }else if(unicode_config.input_mode==UC_LNX){
      matrix_write_P(matrix, os_logo[2][0]);
      matrix_write_P(matrix, PSTR("\n"));
      matrix_write_P(matrix, os_logo[2][1]);
  }else {
      matrix_write_P(matrix, os_logo[3][0]);
      matrix_write_P(matrix, PSTR("\n"));
      matrix_write_P(matrix, os_logo[3][1]);
  }

  matrix_write_P(matrix, PSTR(" "));
  render_layer_status(matrix);
  matrix_write_P(matrix, PSTR("\n"));

  // Host Keyboard LED Status
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ?
                 PSTR("NUMLOCK") : PSTR("       "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ?
                 PSTR("CAPS") : PSTR("    "));
  matrix_write_P(matrix, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ?
                 PSTR("SCLK") : PSTR("    "));
  matrix_write_P(matrix, PSTR("\n"));
  render_rgbled_status(true, matrix);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
    render_rgbled_status(false, &matrix);
    render_layer_status(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif

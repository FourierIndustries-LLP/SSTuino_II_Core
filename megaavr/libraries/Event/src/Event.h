#ifndef EVENT_H
#define EVENT_H

#include <Arduino.h>

#if defined(MEGATINYCORE)
  #if (MEGATINYCORE_SERIES == 0)
    #define TINY_0_SERIES
  #elif (MEGATINYCORE_SERIES == 1)
    #define TINY_1_SERIES
  #elif (MEGATINYCORE_SERIES == 2)
    #define TINY_2_SERIES
  #endif
#endif

namespace event {
#if defined(MEGACOREX) || defined(DXCORE)
  // Features present on all generator channels
  namespace gen {
    enum generator_t : uint8_t {
      disable       = 0x00,
      off           = 0x00,
      updi_synch    = 0x01,
      rtc_ovf       = 0x06,
      rtc_cmp       = 0x07,
      ccl0_out      = 0x10,
      ccl1_out      = 0x11,
      ccl2_out      = 0x12,
      ccl3_out      = 0x13,
      ac0_out       = 0x20,
#if defined(AC1)
      ac1_out       = 0x21,
#endif
#if defined(AC2)
      ac2_out       = 0x22,
#endif
      adc0_ready    = 0x24,
      usart0_xck    = 0x60,
      usart1_xck    = 0x61,
      usart2_xck    = 0x62,
#if defined(USART3)
      usart3_xck    = 0x63,
#endif
      spi0_sck      = 0x68,
      tca0_ovf_lunf = 0x80,
      tca0_hunf     = 0x81,
      tca0_cmp0     = 0x84,
      tca0_cmp1     = 0x85,
      tca0_cmp2     = 0x86,
      tcb0_capt     = 0xA0,
      tcb0          = 0xA0,
      tcb1_capt     = 0xA2,
      tcb1          = 0xA2,
      tcb2_capt     = 0xA4,
      tcb2          = 0xA4,
#if defined(TCB3)
      tcb3_capt     = 0xA6,
      tcb3          = 0xA6,
#endif
#if defined(TCB4)
      tcb4_capt      = 0xA8,
      tcb4           = 0xA8,
#endif
#if defined(__AVR_DA__) || defined(__AVR_DB__)
      ccl4_out      = 0x14,
      ccl5_out      = 0x15,
      zcd0_out      = 0x30,
      zcd1_out      = 0x31,
#if defined(ZCD2)
      zcd2_out      = 0x32,
#endif
#if defined(USART4)
      usart4_xck    = 0x64,
#endif
#if defined(USART5)
      usart5_xck    = 0x65,
#endif
      spi1_sck      = 0x69,
#if defined(TCA1)
      tca1_ovf_lunf = 0x88,
      tca1_hunf     = 0x89,
      tca1_cmp0     = 0x8C,
      tca1_cmp1     = 0x8D,
      tca1_cmp2     = 0x8E,
#endif
#endif // defined(__AVR_DA__) || defined(__AVR_DB__)
#if defined(DXCORE)
// These are present on every modern part released since the 0/1-series and will probably continue to be, so check
      tcb0_ovf      = 0xA1,
      tcb1_ovf      = 0xA3,
#if defined(TCB2)
      tcb2_ovf      = 0xA5,
#endif
#if defined(TCB3)
      tcb3_ovf      = 0xA7,
#endif
#if defined(TCB4)
      tcb4_ovf      = 0xA9,
#endif
#endif
#if defined(TCD0)
      tcd0_cmpbclr  = 0xB0,
      tcd0_cmpaset  = 0xB1,
      tcd0_cmpbset  = 0xB2,
      tcd0_progev   = 0xB3,
#endif
#if defined(MVIO)
      mvio_ok       = 0x05,
#endif
#if defined(ZCD3)
      zcd3_out      = 0x30, // The ZCD is numbered differently, I think just because it's on different pins. Still has the same event channel
#endif
#if defined(__AVR_DB__)
      opamp0_ready  = 0x34,
      opamp1_ready  = 0x35,
#if defined(OPAMP2)
      opamp2_ready  = 0x36,
#endif
#endif // defined(__AVR_DB__)
    };
  };

// Features unique to event generator channel 0
#if defined(EVSYS_CHANNEL0)
  namespace gen0 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      off         = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
      pin_pa0     = 0x40,
      pin_pa1     = 0x41,
#if !defined(DXCORE) || defined(PIN_PA2)
      pin_pa2     = 0x42,
      pin_pa3     = 0x43,
      pin_pa4     = 0x44,
      pin_pa5     = 0x45,
      pin_pa6     = 0x46,
      pin_pa7     = 0x47,
#endif
#if defined(PIN_PB0)
      pin_pb0     = 0x48,
      pin_pb1     = 0x49,
      pin_pb2     = 0x4A,
      pin_pb3     = 0x4B,
      pin_pb4     = 0x4C,
      pin_pb5     = 0x4D,
#endif
#if defined(PIN_PB6)
      pin_pb6     = 0x4E,
      pin_pb7     = 0x4F,
#endif
    };
  };
#endif

// Features unique to event generator channel 1
#if defined(EVSYS_CHANNEL1)
  namespace gen1 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      off         = 0x00,
      rtc_div512  = 0x08,
      rtc_div256  = 0x09,
      rtc_div128  = 0x0A,
      rtc_div64   = 0x0B,
      pin_pa0     = 0x40,
      pin_pa1     = 0x41,
#if defined(PIN_PA2)
      pin_pa2     = 0x42,
      pin_pa3     = 0x43,
      pin_pa4     = 0x44,
      pin_pa5     = 0x45,
      pin_pa6     = 0x46,
      pin_pa7     = 0x47,
#endif
#if defined(PIN_PB0)
      pin_pb0     = 0x48,
      pin_pb1     = 0x49,
      pin_pb2     = 0x4A,
      pin_pb3     = 0x4B,
      pin_pb4     = 0x4C,
      pin_pb5     = 0x4D,
#endif
#if defined(PIN_PB6)
      pin_pb6     = 0x4E,
      pin_pb7     = 0x4F,
#endif
    };
  };
#endif

// Features unique to event generator channel 2
#if defined(EVSYS_CHANNEL2)
  namespace gen2 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      off         = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
#if !defined(DD_14_PINS)  // Can't just check PIN_PC0 - the 0-pin of any port with any pins present is always defined by DxCore.
                          // I considered both ways, but there are to many reasons we need to have the 0-pin defined.
      pin_pc0     = 0x40,
#endif
      pin_pc1     = 0x41,
      pin_pc2     = 0x42,
      pin_pc3     = 0x43,
#if defined(PIN_PC4)
      pin_pc4     = 0x44,
      pin_pc5     = 0x45,
      pin_pc6     = 0x46,
      pin_pc7     = 0x47,
#endif
#if defined(PIN_PD1) // See above for note on PIN_PD0 and why we can't test that, this even impacts DBs.
#if !defined(MVIO) || defined(__AVR_ATmegax09__) || defined(Dx_48_PINS) || defined(Dx_64_PINS)
      pin_pd0     = 0x48,
#endif
      pin_pd1     = 0x49,
      pin_pd2     = 0x4A,
      pin_pd3     = 0x4B,
#endif
      pin_pd4     = 0x4C,
      pin_pd5     = 0x4D,
      pin_pd6     = 0x4E,
      pin_pd7     = 0x4F,
  };
};
#endif

// Features unique to event generator channel 3
#if defined(EVSYS_CHANNEL3)
  namespace gen3 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      off         = 0x00,
      rtc_div512  = 0x08,
      rtc_div256  = 0x09,
      rtc_div128  = 0x0A,
      rtc_div64   = 0x0B,
#if !defined(DD_14_PINS)
      pin_pc0     = 0x40,
#endif
      pin_pc1     = 0x41,
      pin_pc2     = 0x42,
      pin_pc3     = 0x43,
#if defined(PIN_PC4)
      pin_pc4     = 0x44,
      pin_pc5     = 0x45,
      pin_pc6     = 0x46,
      pin_pc7     = 0x47,
#endif
#if defined(PIN_PD1) // See above for note on PIN_PD0 and why we can't test that, this even impacts DBs.
#if !defined(MVIO) || defined(__AVR_ATmegax09__) || defined(Dx_48_PINS) || defined(Dx_64_PINS)
      pin_pd0     = 0x48,
#endif
      pin_pd1     = 0x49,
      pin_pd2     = 0x4A,
      pin_pd3     = 0x4B,
#endif
      pin_pd4     = 0x4C,
      pin_pd5     = 0x4D,
      pin_pd6     = 0x4E,
      pin_pd7     = 0x4F,
    };
  };
#endif

// Features unique to event generator channel 4
#if defined(EVSYS_CHANNEL4)
  namespace gen4 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      off         = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
#if defined(PIN_PE0)
      pin_pe0     = 0x40,
      pin_pe1     = 0x41,
      pin_pe2     = 0x42,
      pin_pe3     = 0x43,
#endif
#if defined(PIN_PE4)
      pin_pe4     = 0x44,
      pin_pe5     = 0x45,
      pin_pe6     = 0x46,
      pin_pe7     = 0x47,
#endif
      pin_pf0     = 0x48,
      pin_pf1     = 0x49,
#if defined(PIN_PF2)
      pin_pf2     = 0x4A,
      pin_pf3     = 0x4B,
      pin_pf4     = 0x4C,
      pin_pf5     = 0x4D,
#endif
      pin_pf6     = 0x4E,
#if defined(PIN_PF7)
      pin_pf7     = 0x4F,
#endif
    };
  };
#endif

// Features unique to event generator channel 5
#if defined(EVSYS_CHANNEL5)
  namespace gen5 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      off         = 0x00,
      rtc_div512  = 0x08,
      rtc_div256  = 0x09,
      rtc_div128  = 0x0A,
      rtc_div64   = 0x0B,
#if defined(PIN_PE0)
      pin_pe0     = 0x40,
      pin_pe1     = 0x41,
      pin_pe2     = 0x42,
      pin_pe3     = 0x43,
#endif
#if defined(PIN_PE4)
      pin_pe4     = 0x44,
      pin_pe5     = 0x45,
      pin_pe6     = 0x46,
      pin_pe7     = 0x47,
#endif
      pin_pf0     = 0x48,
      pin_pf1     = 0x49,
#if defined(PIN_PF2)
      pin_pf2     = 0x4A,
      pin_pf3     = 0x4B,
      pin_pf4     = 0x4C,
      pin_pf5     = 0x4D,
#endif
      pin_pf6     = 0x4E,
#if defined(PIN_PF7)
      pin_pf7     = 0x4F,
#endif
    };
  };
#endif

// Features unique to event generator channel 6
#if defined(EVSYS_CHANNEL6)
  namespace gen6 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      off         = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
#if defined(PIN_PG0)
      pin_pg0     = 0x40,
      pin_pg1     = 0x41,
      pin_pg2     = 0x42,
      pin_pg3     = 0x43,
      pin_pg4     = 0x44,
      pin_pg5     = 0x45,
      pin_pg6     = 0x46,
      pin_pg7     = 0x47,
#endif
    };
  };
#endif

// Features unique to event generator channel 7
#if defined(EVSYS_CHANNEL7)
  namespace gen7 {
    enum generator_t : uint8_t {
      disable    = 0x00,
      off        = 0x00,
      rtc_div512 = 0x08,
      rtc_div256 = 0x09,
      rtc_div128 = 0x0A,
      rtc_div64  = 0x0B,
#if defined(PIN_PG0)
      pin_pg0    = 0x40,
      pin_pg1    = 0x41,
      pin_pg2    = 0x42,
      pin_pg3    = 0x43,
      pin_pg4    = 0x44,
      pin_pg5    = 0x45,
      pin_pg6    = 0x46,
      pin_pg7    = 0x47,
#endif
    };
  };
#endif

// Features unique to event generator channel 8
#if defined(EVSYS_CHANNEL8)
  namespace gen8 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      off         = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
    };
  };
#endif

// Features unique to event generator channel 9
#if defined(EVSYS_CHANNEL9)
  namespace gen9 {
    enum generator_t : uint8_t {
      disable    = 0x00,
      off        = 0x00,
      rtc_div512 = 0x08,
      rtc_div256 = 0x09,
      rtc_div128 = 0x0A,
      rtc_div64  = 0x0B,
    };
  };
#endif


// Generator users
  namespace user {
    enum user_t : uint8_t {
#if defined(MEGACOREX)
      ccl0_event_a   = 0x00,
      ccl0_event_b   = 0x01,
      ccl1_event_a   = 0x02,
      ccl1_event_b   = 0x03,
      ccl2_event_a   = 0x04,
      ccl2_event_b   = 0x05,
      ccl3_event_a   = 0x06,
      ccl3_event_b   = 0x07,
      adc0_start     = 0x08,
      evouta_pin_pa2 = 0x09,
#if defined(PIN_PB2)
      evoutb_pin_pb2 = 0x0A,
#endif
      evoutc_pin_pc2 = 0x0B,
      evoutd_pin_pd2 = 0x0C,
#if defined(PIN_PE2)
      evoute_pin_pe2 = 0x0D,
#endif
      evoutf_pin_pf2 = 0x0E,
      usart0_irda    = 0x0F,
      usart1_irda    = 0x10,
      usart2_irda    = 0x11,
#if defined(USART3)
      usart3_irda    = 0x12,
#endif
      tca0           = 0x13,
      tca0_cnt_a     = 0x13,
      tcb0           = 0x14,
      tcb0_capt      = 0x14,
      tcb1           = 0x15,
      tcb1_capt      = 0x15,
      tcb2           = 0x16,
      tcb2_capt      = 0x16,
#if defined(TCB3)
      tcb3           = 0x17,
      tcb3_capt      = 0x17,
#endif
      // "Unofficial" user generators. Uses EVOUT, but swaps the output pin using PORTMUX
      evouta_pin_pa7 = 0x89,
#if defined(PIN_PC7)
      evoutc_pin_pc7 = 0x8B,
#endif
      evoutd_pin_pd7 = 0x8C,
#endif // defined(MEGACOREX)

#if defined(__AVR_DA__)
      ccl0_event_a   = 0x00,
      ccl0_event_b   = 0x01,
      ccl1_event_a   = 0x02,
      ccl1_event_b   = 0x03,
      ccl2_event_a   = 0x04,
      ccl2_event_b   = 0x05,
      ccl3_event_a   = 0x06,
      ccl3_event_b   = 0x07,
#if defined(LUT4)
      ccl4_event_a   = 0x08,
      ccl4_event_b   = 0x09,
      ccl5_event_a   = 0x0A,
      ccl5_event_b   = 0x0B,
#endif
      adc0_start     = 0x0C,
      ptc_start      = 0x0D,
      evouta_pin_pa2 = 0x0E,
#if defined(PIN_PB2)
      evoutb_pin_pb2 = 0x0F,
#endif
      evoutc_pin_pc2 = 0x10,
      evoutd_pin_pd2 = 0x11,
#if defined(PIN_PE2)
      evoute_pin_pe2 = 0x12,
#endif
#if defined(PIN_PF2)
      evoutf_pin_pf2 = 0x13,
#endif
#if defined(PIN_PG2)
      evoutg_pin_pg2 = 0x14,
#endif
      usart0_irda    = 0x15,
      usart1_irda    = 0x16,
      usart2_irda    = 0x17,
#if defined(USART5)
      usart3_irda    = 0x18,
#endif
#if defined(USART4)
      usart4_irda    = 0x19,
#endif
#if defined(USART5)
      usart5_irda    = 0x1A,
#endif
      tca0           = 0x1B,
      tca0_cnt_a     = 0x1B,
      tca0_cnt_b     = 0x1C,
      tca1           = 0x1D,
      tca1_cnt_a     = 0x1D,
      tca1_cnt_b     = 0x1E,
      tcb0_capt      = 0x1F,
      tcb0           = 0x1F,
      tcb0_cnt       = 0x20,
      tcb1_capt      = 0x21,
      tcb1           = 0x21,
      tcb1_cnt       = 0x22,
      tcb2_capt      = 0x23,
      tcb2           = 0x23,
      tcb2_cnt       = 0x24,
#if defined(TCB3)
      tcb3_capt      = 0x25,
      tcb3           = 0x25,
      tcb3_cnt       = 0x26,
#endif
#if defined(TCB4)
      tcb4_capt      = 0x27,
      tcb4           = 0x27,
      tcb4_cnt       = 0x28,
#endif
      tcd0_in_a      = 0x29,
      tcd0_in_b      = 0x2A,
      // "Unofficial" user generators. Uses EVOUT, but swaps the output pin using PORTMUX
      evouta_pin_pa7 = 0x8E,
#if defined(PIN_PB7)
      evoutb_pin_pb7 = 0x8F,
#endif
#if defined(PIN_PC7)
      evoutc_pin_pc7 = 0x90,
#endif
      evoutd_pin_pd7 = 0x91,
#if defined(PIN_PE7)
      evoute_pin_pe7 = 0x92,
#endif
      // evoutf_pin_pf7 = 0x93, never available on DA/DB
#if defined(PIN_PG7)
      evoutg_pin_pg7 = 0x94,
#endif
#endif // defined(__AVR_DA__)
#if defined(__AVR_DB__)
      ccl0_event_a   = 0x00,
      ccl0_event_b   = 0x01,
      ccl1_event_a   = 0x02,
      ccl1_event_b   = 0x03,
      ccl2_event_a   = 0x04,
      ccl2_event_b   = 0x05,
      ccl3_event_a   = 0x06,
      ccl3_event_b   = 0x07,
#if defined(LUT4)
      ccl4_event_a   = 0x08,
      ccl4_event_b   = 0x09,
      ccl5_event_a   = 0x0A,
      ccl5_event_b   = 0x0B,
#endif
      adc0_start     = 0x0C,
      evouta_pin_pa2 = 0x0D,
#if defined(PIN_PB2)
      evoutb_pin_pb2 = 0x0E,
#endif
      evoutc_pin_pc2 = 0x0F,
      evoutd_pin_pd2 = 0x10,
#if defined(PIN_PE2)
      evoute_pin_pe2 = 0x11,
#endif
#if defined(PIN_PF2)
      evoutf_pin_pf2 = 0x12,
#endif
#if defined(PIN_PG2)
      evoutg_pin_pg2 = 0x13,
#endif
      usart0_irda    = 0x14,
      usart1_irda    = 0x15,
      usart2_irda    = 0x16,
#if defined(USART3)
      usart3_irda    = 0x17,
#endif
#if defined(USART4)
      usart4_irda    = 0x18,
#endif
#if defined(USART5)
      usart5_irda    = 0x19,
#endif
      tca0           = 0x1A,
      tca0_cnt_a     = 0x1A,
      tca0_cnt_b     = 0x1B,
      tca1           = 0x1C,
      tca1_cnt_a     = 0x1C,
      tca1_cnt_b     = 0x1D,
      tcb0_capt      = 0x1E,
      tcb0_cnt       = 0x1F,
      tcb1_capt      = 0x20,
      tcb1_cnt       = 0x21,
      tcb2_capt      = 0x22,
      tcb2_cnt       = 0x23,
#if defined(TCB3)
      tcb3_capt      = 0x24,
      tcb3_cnt       = 0x25,
#endif
#if defined(TCB4)
      tcb4_capt      = 0x26,
      tcb4_cnt       = 0x27,
#endif
      tcd0_in_a      = 0x28,
      tcd0_in_b      = 0x29,
      opamp0_enable  = 0x2A,
      opamp0_disable = 0x2B,
      opamp0_dump    = 0x2C,
      opamp0_drive   = 0x2D,
      opamp1_enable  = 0x2E,
      opamp1_disable = 0x2F,
      opamp1_dump    = 0x30,
      opamp1_drive   = 0x31,
#if defined(OPAMP2)
      opamp2_enable  = 0x32,
      opamp2_disable = 0x33,
      opamp2_dump    = 0x34,
      opamp2_drive   = 0x35,
#endif
      // "Unofficial" user generators. Uses EVOUT, but swaps the output pin using PORTMUX
      evouta_pin_pa7 = 0x8D,
#if defined(PIN_PB7)
      evoutb_pin_pb7 = 0x8E,
#endif
#if defined(PIN_PC7)
      evoutc_pin_pc7 = 0x8F,
#endif
      evoutd_pin_pd7 = 0x90,
#if defined(PIN_PE7)
      evoute_pin_pe7 = 0x91,
#endif
#if defined(PIN_PG7)
      evoutg_pin_pg7 = 0x93,
#endif
#endif // defined(__AVR_DB__)

#if defined(__AVR_DD__)
      ccl0_event_a   = 0x00,
      ccl0_event_b   = 0x01,
      ccl1_event_a   = 0x02,
      ccl1_event_b   = 0x03,
      ccl2_event_a   = 0x04,
      ccl2_event_b   = 0x05,
      ccl3_event_a   = 0x06,
      ccl3_event_b   = 0x07,
      adc0_start     = 0x0C,
#if defined(PIN_PA2) // not on 14-pin ones.
      evouta_pin_pa2 = 0x0D,
#endif
      evoutc_pin_pc2 = 0x0F,
#if defined(PIN_PD2) // only on 28 or 32 pin ones.
      evoutd_pin_pd2 = 0x10,
#endif
#if defined(PIN_PF2) // only on 32-pin ones.
      evoutf_pin_pf2 = 0x12,
#endif
      usart0_irda    = 0x14,
      usart1_irda    = 0x15,
      tca0           = 0x1A,
      tca0_cnt_a     = 0x1A,
      tca0_cnt_b     = 0x1B,
      tcb0           = 0x1E,
      tcb0_capt      = 0x1E,
      tcb0_cnt       = 0x1F,
      tcb1           = 0x20,
      tcb1_capt      = 0x20,
      tcb1_cnt       = 0x21,
      tcb2           = 0x22,
      tcb2_capt      = 0x22,
      tcb2_cnt       = 0x23,
      tcd0_in_a      = 0x28,
      tcd0_in_b      = 0x29,
#if defined(PIN_PA7) // not on 14-pin ones.
      evouta_pin_pa7 = 0x8D,
#endif
#if defined(PIN_PC7)
      evoutc_pin_pc7 = 0x8F,
#endif
      evoutd_pin_pd7 = 0x90,
#endif // __AVR_DD__
  };
};
// END MegaCorex and DxCore definitions


// tinyAVR-2 definitions
#elif defined(TINY_2_SERIES)
  namespace gen {
    enum generator_t : uint8_t {
      disable         = 0x00,
      updi_synch      = 0x1,
      rtc_ovf         = 0x6,
      rtc_cmp         = 0x7,
      ccl0_out        = 0x10,
      ccl1_out        = 0x11,
      ccl2_out        = 0x12,
      ccl3_out        = 0x13,
      ac0_out         = 0x20,
      adc0_ready      = 0x24,
      adc0_sample     = 0x25,
      adc0_window     = 0x26,
      usart0_xck      = 0x60,
      usart1_xck      = 0x61,
      spi0_sck        = 0x68,
      tca0_ovf_lunf   = 0x80,
      tca0_hunf       = 0x81,
      tca0_cmp0       = 0x84,
      tca0_cmp1       = 0x85,
      tca0_cmp2       = 0x86,
      tcb0            = 0xA0,
      tcb0_capt       = 0xA0,
      tcb0_ovf        = 0xA1,
      tcb1            = 0xA2,
      tcb1_capt       = 0xA2,
      tcb1_ovf        = 0xA3,
    };
  };

  namespace gen0 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
      pin_pa0     = 0x40,
      pin_pa1     = 0x41,
      pin_pa2     = 0x42,
      pin_pa3     = 0x43,
      pin_pa4     = 0x44,
      pin_pa5     = 0x45,
      pin_pa6     = 0x46,
      pin_pa7     = 0x47,
      pin_pb0     = 0x40,
      pin_pb1     = 0x41,
      pin_pb2     = 0x42,
      pin_pb3     = 0x43,
#if defined(PIN_PB4)
      pin_pb4     = 0x44,
      pin_pb5     = 0x45,
#endif
#if defined(PIN_PB6)
      pin_pb6     = 0x46,
      pin_pb7     = 0x47,
#endif
    };
  };

  namespace gen1 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      rtc_div512  = 0x08,
      rtc_div256  = 0x09,
      rtc_div128  = 0x0A,
      rtc_div64   = 0x0B,
      pin_pa0     = 0x40,
      pin_pa1     = 0x41,
      pin_pa2     = 0x42,
      pin_pa3     = 0x43,
      pin_pa4     = 0x44,
      pin_pa5     = 0x45,
      pin_pa6     = 0x46,
      pin_pa7     = 0x47,
      pin_pb0     = 0x40,
      pin_pb1     = 0x41,
      pin_pb2     = 0x42,
      pin_pb3     = 0x43,
#if defined(PIN_PB4)
      pin_pb4     = 0x44,
      pin_pb5     = 0x45,
#endif
#if defined(PIN_PB6)
      pin_pb6     = 0x46,
      pin_pb7     = 0x47,
#endif
    };
  };

  namespace gen2 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
#if defined(PIN_PC0)
      pin_pc0     = 0x40,
      pin_pc1     = 0x41,
      pin_pc2     = 0x42,
      pin_pc3     = 0x43,
#endif
#if defined(PIN_PC4)
      pin_pc4     = 0x44,
      pin_pc5     = 0x45,
#endif
      pin_pa0     = 0x40,
      pin_pa1     = 0x41,
      pin_pa2     = 0x42,
      pin_pa3     = 0x43,
      pin_pa4     = 0x44,
      pin_pa5     = 0x45,
      pin_pa6     = 0x46,
      pin_pa7     = 0x47,
    };
  };

  namespace gen3 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      rtc_div512  = 0x08,
      rtc_div256  = 0x09,
      rtc_div128  = 0x0A,
      rtc_div64   = 0x0B,
#if defined(PIN_PC0)
      pin_pc0     = 0x40,
      pin_pc1     = 0x41,
      pin_pc2     = 0x42,
      pin_pc3     = 0x43,
#endif
#if defined(PIN_PC4)
      pin_pc4     = 0x44,
      pin_pc5     = 0x45,
#endif
      pin_pa0     = 0x40,
      pin_pa1     = 0x41,
      pin_pa2     = 0x42,
      pin_pa3     = 0x43,
      pin_pa4     = 0x44,
      pin_pa5     = 0x45,
      pin_pa6     = 0x46,
      pin_pa7     = 0x47,
    };
  };

  namespace gen4 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      rtc_div8192 = 0x08,
      rtc_div4096 = 0x09,
      rtc_div2048 = 0x0A,
      rtc_div1024 = 0x0B,
      pin_pb0     = 0x40,
      pin_pb1     = 0x41,
      pin_pb2     = 0x42,
      pin_pb3     = 0x43,
#if defined(PIN_PB4)
      pin_pb4     = 0x44,
      pin_pb5     = 0x45,
#endif
#if defined(PIN_PB6)
      pin_pb6     = 0x46,
      pin_pb7     = 0x47,
#endif
#if defined(PIN_PC0)
      pin_pc0     = 0x40,
      pin_pc1     = 0x41,
      pin_pc2     = 0x42,
      pin_pc3     = 0x43,
#endif
#if defined(PIN_PC4)
      pin_pc4     = 0x44,
      pin_pc5     = 0x45,
#endif
    };
  };

  namespace gen5 {
    enum generator_t : uint8_t {
      disable     = 0x00,
      rtc_div512  = 0x08,
      rtc_div256  = 0x09,
      rtc_div128  = 0x0A,
      rtc_div64   = 0x0B,
      pin_pb0     = 0x40,
      pin_pb1     = 0x41,
      pin_pb2     = 0x42,
      pin_pb3     = 0x43,
#if defined(PIN_PB4)
      pin_pb4     = 0x44,
      pin_pb5     = 0x45,
#endif
#if defined(PIN_PB6)
      pin_pb6     = 0x46,
      pin_pb7     = 0x47,
#endif
#if defined(PIN_PC0)
      pin_pc0     = 0x40,
      pin_pc1     = 0x41,
      pin_pc2     = 0x42,
      pin_pc3     = 0x43,
#endif
#if defined(PIN_PC4)
      pin_pc4     = 0x44,
      pin_pc5     = 0x45,
#endif
    };
  };


  namespace user {
    enum user_t : uint8_t {
      ccl0_event_a            = 0x00,
      ccl0_event_b            = 0x01,
      ccl1_event_a            = 0x02,
      ccl1_event_b            = 0x03,
      ccl2_event_a            = 0x04,
      ccl2_event_b            = 0x05,
      ccl3_event_a            = 0x06,
      ccl3_event_b            = 0x07,
      adc0_start              = 0x08,
      evouta_pin_pa2          = 0x09,
      evouta_pin_pa7          = 0x89,
      evoutb_pin_pb2          = 0x0A,
#if defined(PIN_PB7)
      evoutb_pin_pb7          = 0x8A,
#endif
#if defined(PIN_PC2)
      evoutc_pin_pc2          = 0x0B,
#endif
      usart0_irda             = 0x0C,
      usart1_irda             = 0x0D,
      tca0                    = 0x0E,
      tca0_cnt_a              = 0x0E,
      tca0_cnt_b              = 0x0F,
      tcb0                    = 0x11,
      tcb0_capt               = 0x11,
      tcb0_cnt                = 0x12,
      tcb1                    = 0x13,
      tcb1_capt               = 0x13,
      tcb1_cnt                = 0x14,
    };
  };

// tinyAVR-0/1 definitions
#elif defined(TINY_0_SERIES) || defined(TINY_1_SERIES)
  namespace gen0 {
    enum generator_t : uint8_t {
#if defined(PIN_PC0)
      pin_pc0      = 0x07,
      pin_pc1      = 0x08,
      pin_pc2      = 0x09,
      pin_pc3      = 0x0A,
#endif
#if defined(PIN_PC4)
      pin_pc4      = 0x0B,
      pin_pc5      = 0x0C,
#endif
      pin_pa0      = 0x0D,
      pin_pa1      = 0x0E,
      pin_pa2      = 0x0F,
      pin_pa3      = 0x10,
      pin_pa4      = 0x11,
      pin_pa5      = 0x12,
      pin_pa6      = 0x13,
      pin_pa7      = 0x14,
#if (PROGMEM_SIZE > 8192 && defined(TINY_1_SERIES))
      tcb1         = 0x15,
      tcb1_capt    = 0x15,
#endif
    };
  };
  namespace gen2 {
    enum generator_t : uint8_t {
      pin_pa0      = 0x0A,
      pin_pa1      = 0x0B,
      pin_pa2      = 0x0C,
      pin_pa3      = 0x0D,
      pin_pa4      = 0x0E,
      pin_pa5      = 0x0F,
      pin_pa6      = 0x10,
      pin_pa7      = 0x11,
      updi         = 0x12,
#if (PROGMEM_SIZE > 8192 && defined(TINY_1_SERIES))
      ac1_out      = 0x13,
      ac2_out      = 0x14,
#endif
    };
  };

// Only on parts with > 8 pins does this have any unique options
#if defined(__AVR_ATtinyxy4__) || defined(__AVR_ATtinyxy6__) || defined(__AVR_ATtinyxy7__)
  namespace gen3 {
    enum generator_t : uint8_t {
      pin_pb0      = 0x0A,
      pin_pb1      = 0x0B,
      pin_pb2      = 0x0C,
      pin_pb3      = 0x0D,
#if defined(PIN_PB4)
      pin_pb4      = 0x0E,
      pin_pb5      = 0x0F,
#endif
#if defined(PIN_PB6)
      pin_pb6      = 0x10,
      pin_pb7      = 0x11,
#endif
#if (PROGMEM_SIZE > 8192 && MEGATINYCORE_SERIES == 1)
      ac1_out      = 0x12,
      ac2_out      = 0x13,
#endif
    };
  };
#endif

#if defined(TINY_1_SERIES)

#if defined(__AVR_ATtinyxy4__) || defined(__AVR_ATtinyxy6__) || defined(__AVR_ATtinyxy7__)
  // Only 1-series parts have second sync channel.
  // Only on parts with > 8 pins does it have any unique options
  namespace gen1 {
    enum generator_t : uint8_t {
      pin_pb0      = 0x08,
      pin_pb1      = 0x09,
      pin_pb2      = 0x0A,
      pin_pb3      = 0x0B,
#if defined(PIN_PB0)
      pin_pb4      = 0x0C,
      pin_pb5      = 0x0D,
#endif
#if defined(PIN_PB6)
      pin_pb6      = 0x0E,
      pin_pb7      = 0x0F,
#endif
#if (PROGMEM_SIZE > 8192) // Only 16/32k 1-series, but only 1-series is here
      tcb1         = 0x10,
      tcb1_capt    = 0x10,
#endif
    };
  };
#endif

  // Only 1-series parts have third and fourth async sync channel.
  // and only parts with 20/24 pins, or the 1614 have any items on this list available
#if !(defined(__AVR_ATtinyxy2__) || (defined(__AVR_ATtinyxy4__) && PROGMEM_SIZE <= 8192))
  namespace gen4 {
    enum generator_t : uint8_t {
#if defined(PIN_PC0)
      pin_pc0      = 0x0A,
      pin_pc1      = 0x0B,
      pin_pc2      = 0x0C,
      pin_pc3      = 0x0D,
#endif
#if defined(PIN_PC4)
      pin_pc4      = 0x0E,
      pin_pc5      = 0x0F,
#endif
#if (PROGMEM_SIZE > 8192) // Only 16/32k 1-series, but only 1-series is here
      ac1_out      = 0x10,
      ac2_out      = 0x11,
#endif
    };
  };
#endif

  namespace gen5 {
    enum generator_t : uint8_t {
      rtc_div8192       = 0x0A,
      rtc_div4096       = 0x0B,
      rtc_div2048       = 0x0C,
      rtc_div1024       = 0x0D,
      rtc_div512        = 0x0E,
      rtc_div256        = 0x0F,
      rtc_div128        = 0x10,
      rtc_div64         = 0x11,
#if (PROGMEM_SIZE > 8192) // Only 16/32k 1-series
      ac1_out           = 0x12,
      ac2_out           = 0x13,
#endif
    };
  };
#endif // end of  1-series only part.

  namespace gens {
    enum generator_t : uint8_t {
      disable           = 0x00,
      off               = 0x00,
      tcb0              = 0x01,
      tcb0_capt         = 0x01,
      tca0_ovf_lunf     = 0x02,
      tca0_hunf         = 0x03,
      tca0_cmp0         = 0x04,
      tca0_cmp1         = 0x05,
      tca0_cmp2         = 0x06,
    };
  };

  namespace gen {
    enum generator_t : uint8_t {
      disable           = 0x00,
      off               = 0x00,
      ccl_lut0          = 0x01,
      ccl_lut1          = 0x02,
      ac0_out           = 0x03,
#if defined(TINY_1_SERIES)
      tcd0_cmpbclr      = 0x04,
      tcd0_cmpaset      = 0x05,
      tcd0_cmpbset      = 0x06,
      tcd0_progev       = 0x07,
#endif
      rtc_ovf           = 0x08,
      rtc_cmp           = 0x09,
    };
  };

  namespace user {
    enum user_t : uint8_t {
      tcb0                    = 0x00,
      tcb0_capt               = 0x00,
      adc0_start              = 0x01,
      ccl0_event_a            = 0x02,
      ccl1_event_a            = 0x03,
      ccl0_event_b            = 0x04,
      ccl1_event_b            = 0x05,
      tcd0_in_a               = 0x06,
      tcd0_in_b               = 0x07,
      evouta_pin_pa2          = 0x08,
      evoutb_pin_pb2          = 0x09,
      evoutc_pin_pc2          = 0x0A,
      tcb1                    = 0x0B,
      tcb1_capt               = 0x0B,
      adc1_start              = 0x0c,
      tca0                    = 0x10,
      tca0_cnt_a              = 0x10,
      usart0_irda             = 0x11,
    };
  };
#endif // TINY_0_SERIES || TINY_1_SERIES
};

// Legacy definitions
namespace user { using namespace event::user; };
namespace gen  { using namespace event::gen;  };
#if defined(EVSYS_CHANNEL0)
namespace gen0 { using namespace event::gen0; };
#endif
#if defined(EVSYS_CHANNEL1)
namespace gen1 { using namespace event::gen1; };
#endif
#if defined(EVSYS_CHANNEL2)
namespace gen2 { using namespace event::gen2; };
#endif
#if defined(EVSYS_CHANNEL3)
namespace gen3 { using namespace event::gen3; };
#endif
#if defined(EVSYS_CHANNEL4)
namespace gen4 { using namespace event::gen4; };
#endif
#if defined(EVSYS_CHANNEL5)
namespace gen5 { using namespace event::gen5; };
#endif
#if defined(EVSYS_CHANNEL6)
namespace gen6 { using namespace event::gen6; };
#endif
#if defined(EVSYS_CHANNEL7)
namespace gen7 { using namespace event::gen7; };
#endif
#if defined(EVSYS_CHANNEL8)
namespace gen8 { using namespace event::gen8; };
#endif
#if defined(EVSYS_CHANNEL9)
namespace gen9 { using namespace event::gen9; };
#endif
#if defined(TINY_0_SERIES) || defined(TINY_1_SERIES)
namespace gens { using namespace event::gens; };
#endif

class Event {
  public:
    Event(uint8_t channel_num, volatile uint8_t &channel_addr);
    uint8_t get_channel_number();
    static Event& get_channel(uint8_t channel_number);
    static Event& get_generator_channel(event::gen::generator_t generator);
    static Event& get_generator_channel(uint8_t generator_pin);
    uint8_t get_generator();
    void set_generator(event::gen::generator_t generator);
    static Event& assign_generator(event::gen::generator_t event_generator);
    void set_generator(uint8_t pin_number);
    static Event& assign_generator_pin(uint8_t port, uint8_t port_pin);
    static Event& assign_generator_pin(uint8_t pin_number);
    static int8_t get_user_channel_number(event::user::user_t event_user);
    static Event& get_user_channel(event::user::user_t event_user);
    void set_user(event::user::user_t event_user);
    int8_t set_user_pin(uint8_t pin_number);
    static void clear_user(event::user::user_t event_user);
    void soft_event();
    void long_soft_event(uint8_t length);
    // event_types: They start from 0x00 for inputs, outputs start at 0x40
    static event::gen::generator_t gen_from_peripheral(AC_t&  comp);
    static event::gen::generator_t gen_from_peripheral(CCL_t& logic, uint8_t event_type = 0);
    static event::user::user_t    user_from_peripheral(CCL_t& logic, uint8_t user_type  = 0);
    static event::gen::generator_t gen_from_peripheral(TCA_t& timer, uint8_t event_type = 0);
    static event::user::user_t    user_from_peripheral(TCA_t& timer, uint8_t user_type  = 0);
    static event::gen::generator_t gen_from_peripheral(TCB_t& timer, uint8_t event_type = 0);
    static event::user::user_t    user_from_peripheral(TCB_t& timer, uint8_t user_type  = 0);
    static event::user::user_t    user_from_peripheral(USART_t& usart);
    void start(bool state = true);
    void stop();

    #if defined(EVSYS_CHANNEL0)
      void get_generator_channel(event::gen0::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen0::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif
    #if defined(EVSYS_CHANNEL1)
      void get_generator_channel(event::gen1::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen1::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif
    #if defined(EVSYS_CHANNEL2)
      void get_generator_channel(event::gen2::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen2::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif
    #if defined(EVSYS_CHANNEL3)
      void get_generator_channel(event::gen3::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen3::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif
    #if defined(EVSYS_CHANNEL4)
      void get_generator_channel(event::gen4::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen4::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif
    #if defined(EVSYS_CHANNEL5)
      void get_generator_channel(event::gen5::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen5::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif
    #if defined(EVSYS_CHANNEL6)
      void get_generator_channel(event::gen6::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen6::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif
    #if defined(EVSYS_CHANNEL7)
      void get_generator_channel(event::gen7::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen7::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif
    #if defined(EVSYS_CHANNEL8)
      void get_generator_channel(event::gen8::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen8::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif
    #if defined(EVSYS_CHANNEL9)
      void get_generator_channel(event::gen9::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen9::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif
    #if defined(TINY_0_SERIES) || defined(TINY_1_SERIES)
      void get_generator_channel(event::gens::generator_t generator) { get_generator_channel((event::gen::generator_t)generator); }
      void set_generator(event::gen::generator_t generator) { set_generator((event::gen::generator_t)generator); }
    #endif

  private:
    const uint8_t channel_number;      // Holds the event generator channel number
    volatile uint8_t &channel_address; // Reference to the event channel address
    uint8_t generator_type;            // Generator type the event channel is using
};

#if defined(MEGACOREX) || defined(DXCORE) || defined(TINY_2_SERIES)
  #if defined(EVSYS_CHANNEL0)
    extern Event Event0;
  #endif
  #if defined(EVSYS_CHANNEL1)
    extern Event Event1;
  #endif
  #if defined(EVSYS_CHANNEL2)
    extern Event Event2;
  #endif
  #if defined(EVSYS_CHANNEL3)
    extern Event Event3;
  #endif
  #if defined(EVSYS_CHANNEL4)
    extern Event Event4;
  #endif
  #if defined(EVSYS_CHANNEL5)
    extern Event Event5;
  #endif
  #if defined(EVSYS_CHANNEL6)
    extern Event Event6;
  #endif
  #if defined(EVSYS_CHANNEL7)
    extern Event Event7;
  #endif
  #if defined(EVSYS_CHANNEL8)
    extern Event Event8;
  #endif
  #if defined(EVSYS_CHANNEL9)
    extern Event Event9;
  #endif

// tinyAVR-0/1
#else
#if defined(EVSYS_SYNCCH0)
  extern Event Event0;
  #define EventSync0     Event0
  #define EVSYS_CHANNEL0 EVSYS_SYNCCH0
#endif
#if defined(EVSYS_SYNCCH1)
  extern Event Event1;
  #define EventSync1     Event1
  #define EVSYS_CHANNEL1 EVSYS_SYNCCH1
#endif
#if defined(EVSYS_ASYNCCH0)
  extern Event Event2;
  #define EventAsync0    Event2
  #define EVSYS_CHANNEL2 EVSYS_ASYNCCH0
#endif
#if defined(EVSYS_ASYNCCH1)
  extern Event Event3;
  #define EventAsync1    Event3
  #define EVSYS_CHANNEL3 EVSYS_ASYNCCH1
#endif
#if defined(EVSYS_ASYNCCH2)
  extern Event Event4;
  #define EventAsync2    Event4
  #define EVSYS_CHANNEL4 EVSYS_ASYNCCH2
#endif
#if defined(EVSYS_ASYNCCH3)
  extern Event Event5;
  #define EventAsync3    Event5
  #define EVSYS_CHANNEL5 EVSYS_ASYNCCH3
#endif
#if defined(EVSYS_SYNCUSER0)
  #define EVSYS_USERTCA0CNTA EVSYS_SYNCUSER0
#endif
#if defined(EVSYS_SYNCUSER1)
  #define EVSYS_USERUSART0IRDA EVSYS_SYNCUSER1
#endif
#if defined(EVSYS_ASYNCUSER0)
  #define EVSYS_USERTCB0CAPT EVSYS_ASYNCUSER0
#endif
#if defined(EVSYS_ASYNCUSER1)
  #define EVSYS_USERADC0START EVSYS_ASYNCUSER1
#endif
#if defined(EVSYS_ASYNCUSER2)
  #define EVSYS_USERCCLLUT0A EVSYS_ASYNCUSER2
#endif
#if defined(EVSYS_ASYNCUSER3)
  #define EVSYS_USERCCLLUT1A EVSYS_ASYNCUSER3
#endif
#if defined(EVSYS_ASYNCUSER4)
  #define EVSYS_USERCCLLUT0B EVSYS_ASYNCUSER4
#endif
#if defined(EVSYS_ASYNCUSER5)
  #define EVSYS_USERCCLLUT1B EVSYS_ASYNCUSER5
#endif
#if defined(EVSYS_ASYNCUSER6)
  #define EVSYS_USERTCD0INPUTA EVSYS_ASYNCUSER6
#endif
#if defined(EVSYS_ASYNCUSER7)
  #define EVSYS_USERTCD0INPUTB EVSYS_ASYNCUSER7
#endif
#if defined(EVSYS_ASYNCUSER8)
  #define EVSYS_USEREVSYSEVOUTA EVSYS_ASYNCUSER8
#endif
#if defined(EVSYS_ASYNCUSER9)
  #define EVSYS_USEREVSYSEVOUTB EVSYS_ASYNCUSER9
#endif
#if defined(EVSYS_ASYNCUSER10)
  #define EVSYS_USEREVSYSEVOUTC EVSYS_ASYNCUSER10
#endif
#if defined(EVSYS_ASYNCUSER11)
  #define EVSYS_USERTCB1CAPT EVSYS_ASYNCUSER11
#endif
#if defined(EVSYS_ASYNCUSER12)
  #define EVSYS_USERADC1START EVSYS_ASYNCUSER12
#endif
#endif // tinyAVR-0/1

#endif // EVENT_H

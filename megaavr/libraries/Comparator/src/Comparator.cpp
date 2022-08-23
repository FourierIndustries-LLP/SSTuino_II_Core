#include "Comparator.h"

AnalogComparator Comparator(0, AC0);

AnalogComparator::AnalogComparator(const uint8_t comp_number, AC_t& ac) : comparator_number(comp_number), AC(ac)
{
}

void AnalogComparator::init()
{
  // Set voltage reference
  if(reference != comparator::ref::disable)
  {
    VREF.CTRLA = (VREF.CTRLA & ~VREF_AC0REFSEL_AVDD_gc) | reference;
    VREF.CTRLB = VREF_AC0REFEN_bm;
  }
  else
    VREF.CTRLB &= ~VREF_AC0REFEN_bm;

  // Set DACREF
  AC.DACREF = dacref;

  // Set hysteresis and output pin state
  AC.CTRLA = (AC.CTRLA & ~AC_HYSMODE_gm) | hysteresis | (output & AC_OUTEN_bm);

  // Clear input pins
  if(input_p == comparator::in_p::in0)
    PORTD.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;
  else if(input_p == comparator::in_p::in1)
    PORTD.PIN4CTRL = PORT_ISC_INPUT_DISABLE_gc;
  else if(input_p == comparator::in_p::in2)
    PORTD.PIN6CTRL = PORT_ISC_INPUT_DISABLE_gc;
  else if(input_p == comparator::in_p::in3)
    PORTD.PIN1CTRL = PORT_ISC_INPUT_DISABLE_gc;
  if(input_n == comparator::in_n::in0)
    PORTD.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
  else if(input_n == comparator::in_n::in1)
    PORTD.PIN5CTRL = PORT_ISC_INPUT_DISABLE_gc;
  else if(input_n == comparator::in_n::in2)
    PORTD.PIN7CTRL = PORT_ISC_INPUT_DISABLE_gc;

  // Set positive and negative pins, invert output if defined by the user
  AC.MUXCTRLA = (AC.MUXCTRLA & ~0x1B) | (input_p << 3) | input_n | (output & AC_INVERT_bm);

  // Set output if enabled
  if(output & AC_OUTEN_bm)
    PORTA.DIRSET = PIN7_bm;
  else
    PORTA.DIRCLR = PIN7_bm;
}

void AnalogComparator::start(bool state)
{
  if(state)
    AC.CTRLA |= AC_ENABLE_bm;
  else
    AC.CTRLA &= ~AC_ENABLE_bm;
}

void AnalogComparator::stop()
{
  start(false);
}

bool AnalogComparator::read()
{
  return !!(AC0.STATUS & AC_STATE_bm);
}

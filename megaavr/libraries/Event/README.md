# Event
A library for interfacing with the built-in Event system on the megaAVR-0 series MCUs.
Developed by [MCUdude](https://github.com/MCUdude/).

**From the datasheet:**
> The Event System (EVSYS) enables direct peripheral-to-peripheral signaling. It allows a change in one peripheral (the event generator) to trigger actions in other peripherals (the event users) through event channels, without using the CPU. It is designed to provide short and predictable response times between peripherals, allowing for autonomous peripheral control and interaction, and also for synchronized timing of actions in several peripheral modules. It is thus a powerful tool for reducing the complexity, size, and execution time of the software.


## Overview
The event system allows routing of signals from event "generators" (outputs on various peripherals) through an event "channel", which one or more "event users" can be connected. When an event signal coming from the generator is is "active" or "high", the users connected to the same channel as the generator will perform certain specified actions depending on the peripheral. Generators are often the sorts of things that generate an interrupt if that is enabled - but some things can generate constant level events (such as following the state of a pin).
The event users can do a wide variety of things. The ADC can kick off a staged measurement. Type A and B timers can count them, and type B timers can measure their duration or time between them with input capture. USARTs can even use them as their RX input! This is nice and all - but what really makes the Event system reach it's potential is CCL (configurable custom logic) which can use events as inputs, in addiion to having access to several more internal sourcesof "event-like" signals - and being event generators in their own right.

More information about the Event system and how it works can be found in the [Microchip Application Note AN2451](http://ww1.microchip.com/downloads/en/AppNotes/DS00002451B.pdf) and in the [megaAVR-0 family data sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/megaAVR0-series-Family-Data-Sheet-DS40002015B.pdf).


### Level vs. Pulse events
There are two types of events - a "pulse" interrupt, which lasts for the duration of a single clock cycle (either `CLK_PER` or a relevant (slower) clock - for example, the USART XCK generator provides a pulse event which lasts one XCK period, whuich is far slower than CLK_PER), or a "level" interrupt which lasts for the duration of some condition.
Often for a given even generator or user only one or the other makes sense. Less often, for some reason or another, you may need a level event, but all you have is a pulse event - or the other way around. A [CCL module (Logic.h)](../Logic/README.md) event between the two at the cost of the logic module and one event channel. In the case of timer WO (PWM) channels, the CCL already has level inputs.


### Synchronization
>Events can be either synchronous or asynchronous to the peripheral clock. Each Event System channel has two subchannels: one asynchronous and one synchronous.
>The asynchronous subchannel is identical to the event output from the generator. If the event generator generates a signal asynchronous to the peripheral clock, the signal on the asynchronous subchannel will be asynchronous. If the event generator generates a signal synchronous to the peripheral clock, the signal on the asynchronous subchannel
>will also be synchronous.
>The synchronous subchannel is identical to the event output from the generator, if the event generator generates a signal synchronous to the peripheral clock. If the event generator generates a signal asynchronous to the peripheral clock, this signal is first synchronized before being routed onto the synchronous subchannel. Depending on when the event occurs, synchronization will delay the it by two to three clock cycles. The Event System automatically perform this synchronization if an asynchronous generator is selected for an event channel.

The event system, under the hood, is asynchronous - it can react faster than the system clock (often a lot faster).
The fact that it is asynchronous usually doesn't matter, but it is one of the things one should keep in mind when using these features, because every so often it does.


## Event
Class for interfacing with the Event system (EVSYS). Each event channel has its own object.
Use the predefined objects `Event0`, `Event1`, `Event2`, `Event3`, `Event4`, `Event5`, `Event6` or `Event7`. Refer to static functions by using `Event::`. Additionally, there is an `Event_empty` that is returned whenever you call a method that returns an Event reference, but it can't fulfil your request.
Note that different channels have different functionality, so make sure you use the right channel for the task.


In short terms:
* `event::genN::rtc_div8192`, `event::genN::rtc_div4096`, `event::genN::rtc_div2048` and `event::genN::rtc_div1024` are only available on odd numbered channels
* `event::genN::rtc_div512`, `event::genN::rtc_div256`, `event::genN::rtc_div128` and `event::genN::rtc_div64` are only available on even numbered channels
* PIN PA0..7 and PB0..5 can only be used as event generators on channel 0 and 1
* PIN PC0..7 and PD0..7 can only be used as event generators on channel 2 and 3
* PIN PE0..3 and PF0..6 can only be used as event generators on channel 4 and 5


## get_channel_number()
Function to get the current channel number. Useful if the channel object has been passed to a function as reference. The `Event_empty` object has channel number 255.

### Declaration
``` c++
uint8_t get_channel_number();
```

### Usage
``` c++
uint8_t this_channel = Event0.get_channel_number();  // In this case, get_channel_number will return 0
```


## get_channel()
Static function that returns the event object of that number. Useful if you need to get the correct Event object based on an integer number.

### Declaration
``` c++
static Event& get_channel(uint8_t channel_number);
```

### Usage
```c++
// Create a reference to the object get_channel() returns, which in this case will be the Event2 object
// myEvent can be futher used as a regular object
Event& myEvent = Event::get_channel(2);

// Simple check to compare two objects
if(&myEvent == &Event2)
{
  // myEvent and Event2 is the same thing!
}
```


## get_generator_channel()
Static function that returns the object used for a particular event generator. Useful to figure out which channel or object a generator is connected to.
Returns a reference to the `Event_empty` object if the generator is not connected to any channel.

### Declaration
``` c++
static Event& get_generator_channel(event::gen::generator_t generator); // For all other generators (event::gen, event::gen0...gen7)
static Event& get_generator_channel(uint8_t generator);                 // For Arduino pins
```

### Usage
```c++
// Set ccl0_out as event generator for channel 2
Event2.set_generator(event::gen::ccl0_out);

// Now we want to get the channel/object connected to the ccl0_out generator
// Create a reference to the object get_generator_channel() returns.
Event& myEvent = Event::get_generator_channel(event::gen::ccl0_out);

// myEvent is now a reference to Event2!
```


## get_generator()
Function to get the generator used for a particular channel.

### Declaration
``` c++
uint8_t get_generator();
```

### Usage
```c++
uint8_t generator_used = Event0.get_generator();
if(generator_used == event::gen::ccl0_out) {
  Serial.println("We're using event::gen::ccl0_out as generator");
}
```


## set_generator(event::gen::generator_t)
Function to connect an event generator to a channel. Note that we use the prefix event::genN:: (where N is the channel number) when referring to generators unique to this particular channel. we use event::gen:: when referring to generators available on all generators.

### Declaration
``` c++
void set_generator(event::gen::generator_t generator);
void set_generator(event::gen0::generator_t generator);
//...
void set_generator(event::gen7::generator_t generator);
```

### Usage
```c++
Event0.set_generator(event::gen::ccl0_out); // Use the output of logic block 0 (CCL0) as an event generator for Event0
Event2.set_generator(event::gen2::pin_pc0); // Use pin PC0 as an event generator for Event2
```

### Generator table
Below is a table with all possible generators for each channel.

| All event channels          | Event0                                                     | Event1                                                     | Event2                                                     | Event3                                                     | Event4                                                      | Event5                                                      | Event6                     | Event7                    |
|-----------------------------|------------------------------------------------------------|------------------------------------------------------------|------------------------------------------------------------|------------------------------------------------------------|-------------------------------------------------------------|-------------------------------------------------------------|----------------------------|---------------------------|
| `event::gen::disable`       | `event::gen0::disable`                                     | `event::gen1::disable`                                     | `event::gen2::disable`                                     | `event::gen3::disable`                                     | `event::gen4::disable`                                      | `event::gen5::disable`                                      | `event::gen6::disable`     | `event::gen7::disable`    |
| `event::gen::updi_synch`    | `event::gen0::rtc_div8192`                                 | `event::gen1::rtc_div512`                                  | `event::gen2::rtc_div8192`                                 | `event::gen3::rtc_div512`                                  | `event::gen4::rtc_div8192`                                  | `event::gen5::rtc_div512`                                   | `event::gen6::rtc_div8192` | `event::gen7::rtc_div512` |
| `event::gen::rtc_ovf`       | `event::gen0::rtc_div4096`                                 | `event::gen1::rtc_div256`                                  | `event::gen2::rtc_div4096`                                 | `event::gen3::rtc_div256`                                  | `event::gen4::rtc_div4096`                                  | `event::gen5::rtc_div256`                                   | `event::gen6::rtc_div4096` | `event::gen7::rtc_div256` |
| `event::gen::rtc_cmp`       | `event::gen0::rtc_div2048`                                 | `event::gen1::rtc_div128`                                  | `event::gen2::rtc_div2048`                                 | `event::gen3::rtc_div128`                                  | `event::gen4::rtc_div2048`                                  | `event::gen5::rtc_div128`                                   | `event::gen6::rtc_div2048` | `event::gen7::rtc_div128` |
| `event::gen::ccl0_out`      | `event::gen0::rtc_div1024`                                 | `event::gen1::rtc_div64`                                   | `event::gen2::rtc_div1024`                                 | `event::gen3::rtc_div64`                                   | `event::gen4::rtc_div1024`                                  | `event::gen5::rtc_div64`                                    | `event::gen6::rtc_div1024` | `event::gen7::rtc_div64`  |
| `event::gen::ccl1_out`      | `event::gen0::pin_pa0`                                     | `event::gen1::pin_pa0`                                     | `event::gen2::pin_pc0`                                     | `event::gen3::pin_pc0`                                     | `event::gen4::pin_pe0`<br/> (Only available on ATmegaX809)  | `event::gen5::pin_pe0`<br/> (Only available on ATmegaX809)  |                            |                           |
| `event::gen::ccl2_out`      | `event::gen0::pin_pa1`                                     | `event::gen1::pin_pa1`                                     | `event::gen2::pin_pc1`                                     | `event::gen3::pin_pc1`                                     | `event::gen4::pin_pe1`<br/> (Only available on ATmegaX809)  | `event::gen5::pin_pe1`<br/> (Only available on ATmegaX809)  |                            |                           |
| `event::gen::ccl3_out`      | `event::gen0::pin_pa2`                                     | `event::gen1::pin_pa2`                                     | `event::gen2::pin_pc2`                                     | `event::gen3::pin_pc2`                                     | `event::gen4::pin_pe2`<br/> (Only available on ATmegaX809)  | `event::gen5::pin_pe2`<br/> (Only available on ATmegaX809)  |                            |                           |
| `event::gen::ac0_out`       | `event::gen0::pin_pa3`                                     | `event::gen1::pin_pa3`                                     | `event::gen2::pin_pc3`                                     | `event::gen3::pin_pc3`                                     | `event::gen4::pin_pe3`<br/> (Only available on ATmegaX809)  | `event::gen5::pin_pe3`<br/> (Only available on ATmegaX809)  |                            |                           |
| `event::gen::adc0_ready`    | `event::gen0::pin_pa4`                                     | `event::gen1::pin_pa4`                                     | `event::gen2::pin_pc4`<br/> (Only available on ATmegaX809) | `event::gen3::pin_pc4`<br/> (Only available on ATmegaX809) |                                                             |                                                             |                            |                           |
| `event::gen::usart0_xck`    | `event::gen0::pin_pa5`                                     | `event::gen1::pin_pa5`                                     | `event::gen2::pin_pc5`<br/> (Only available on ATmegaX809) | `event::gen3::pin_pc5`<br/> (Only available on ATmegaX809) |                                                             |                                                             |                            |                           |
| `event::gen::usart1_xck`    | `event::gen0::pin_pa6`                                     | `event::gen1::pin_pa6`                                     | `event::gen2::pin_pc6`<br/> (Only available on ATmegaX809) | `event::gen3::pin_pc6`<br/> (Only available on ATmegaX809) |                                                             |                                                             |                            |                           |
| `event::gen::usart2_xck`    | `event::gen0::pin_pa7`                                     | `event::gen1::pin_pa7`                                     | `event::gen2::pin_pc7`<br/> (Only available on ATmegaX809) | `event::gen3::pin_pc7`<br/> (Only available on ATmegaX809) |                                                             |                                                             |                            |                           |
| `event::gen::usart3_xck`    | `event::gen0::pin_pb0`<br/> (Only available on ATmegaX809) | `event::gen1::pin_pb0`<br/> (Only available on ATmegaX809) | `event::gen2::pin_pd0`                                     | `event::gen3::pin_pd0`                                     | `event::gen4::pin_pf0`                                      | `event::gen5::pin_pf0`                                      |                            |                           |
| `event::gen::spi0_sck`      | `event::gen0::pin_pb1`<br/> (Only available on ATmegaX809) | `event::gen1::pin_pb1`<br/> (Only available on ATmegaX809) | `event::gen2::pin_pd1`                                     | `event::gen3::pin_pd1`                                     | `event::gen4::pin_pf1`                                      | `event::gen5::pin_pf1`                                      |                            |                           |
| `event::gen::tca0_ovf_lunf` | `event::gen0::pin_pb2`<br/> (Only available on ATmegaX809) | `event::gen1::pin_pb2`<br/> (Only available on ATmegaX809) | `event::gen2::pin_pd2`                                     | `event::gen3::pin_pd2`                                     | `event::gen4::pin_pf2`<br/> (Not available on 28-pin parts) | `event::gen5::pin_pf2`<br/> (Not available on 28-pin parts) |                            |                           |
| `event::gen::tca0_hunf`     | `event::gen0::pin_pb3`<br/> (Only available on ATmegaX809) | `event::gen1::pin_pb3`<br/> (Only available on ATmegaX809) | `event::gen2::pin_pd3`                                     | `event::gen3::pin_pd3`                                     | `event::gen4::pin_pf3`<br/> (Not available on 28-pin parts) | `event::gen5::pin_pf3`<br/> (Not available on 28-pin parts) |                            |                           |
| `event::gen::tca0_cmp0`     | `event::gen0::pin_pb4`<br/> (Only available on ATmegaX809) | `event::gen1::pin_pb4`<br/> (Only available on ATmegaX809) | `event::gen2::pin_pd4`                                     | `event::gen3::pin_pd4`                                     | `event::gen4::pin_pf4`<br/> (Not available on 28-pin parts) | `event::gen5::pin_pf4`<br/> (Not available on 28-pin parts) |                            |                           |
| `event::gen::tca0_cmp1`     | `event::gen0::pin_pb5`<br/> (Only available on ATmegaX809) | `event::gen1::pin_pb5`<br/> (Only available on ATmegaX809) | `event::gen2::pin_pd5`                                     | `event::gen3::pin_pd5`                                     | `event::gen4::pin_pf5`<br/> (Not available on 28-pin parts) | `event::gen5::pin_pf5`<br/> (Not available on 28-pin parts) |                            |                           |
| `event::gen::tca0_cmp2`     |                                                            |                                                            | `event::gen2::pin_pd6`                                     | `event::gen3::pin_pd6`                                     | `event::gen4::pin_pf6`                                      | `event::gen5::pin_pf6`                                      |                            |                           |
| `event::gen::tcb0_capt`     |                                                            |                                                            | `event::gen2::pin_pd7`                                     | `event::gen3::pin_pd7`                                     |                                                             |                                                             |                            |                           |
| `event::gen::tcb1_capt`     |                                                            |                                                            |                                                            |                                                            |                                                             |                                                             |                            |                           |
| `event::gen::tcb2_capt`     |                                                            |                                                            |                                                            |                                                            |                                                             |                                                             |                            |                           |
| `event::gen::tcb3_capt`     |                                                            |                                                            |                                                            |                                                            |                                                             |                                                             |                            |                           |
| `event::gen::tcb3_capt`     |                                                            |                                                            |                                                            |                                                            |                                                             |                                                             |                            |                           |


### assign_generator(event::gen::generator_t)
Static function that connects an event generator to a channel. What's different compared to `set_generator()` is that this function returns a reference to the channel object the generator has been assigned to. In other words, you don't need to keep track of the exact channel number, it just assigns an available channel.
Note that this function only accepts generators that are present on all channels (event::gen::). It will return a reference to the `Event_empty` object if no channel is available.

### Declaration
``` c++
static Event& assign_generator(event::gen::generator_t event_generator);
```

### Usage
```c++
Event& myEvent = Event::assign_generator(event::gen::ac0_out); // Assign the AC0 out generator to a channel
myEvent.start();
```


## set_generator(uint8_t pin_number)
Function that sets an Arduino pin as the event generator. Note that you will have to make sure a particular pin can be used as an event generator for the selected channel/object. **If this sounds like a hassle, use [assign_generator_pin()](#assign_generator_pin) instead.**

### Declaration
``` c++
void set_generator(uint8_t pin_number);
```

### Usage
```c++
Event0.set_generator(PIN_PA0); // Will work. PA0 can be used as an event generator for channel 0
Event1.set_generator(PIN_PC3); // WILL NOT WORK! PORTC cannot be used as an event generator for channel 1
```


## assign_generator_pin()
Static function that sets an Arduino pin as the event generator. Unlike set_generator(uint8_t pin_number), this function will return the object the generator has been assigned to. It will always try to use the lowest possible channel number as possible, and will return a reference to the object `Event_empty` (generator number 255) if the pin can't be assigned to a channel.

### Declaration
``` c++
static Event& assign_generator_pin(uint8_t pin_number);
```

### Usage
```c++
// We're using PIN_PE2 as event generator, and the library finds a suited object
Event& myEvent = Event::assign_generator_pin(PIN_PE2);

// The myEvent object can be used directly
myEvent.start();
```


## get_user_channel_number()
Static function to get what event channel a user is connected to. Returns -1 if not connected to any channel.
Note that we use `event::user::` as prefix when we refer to event users. Since this is a static function you don't have to specify an object to determine what channel the user is connected to. An event channel, and hence an event generator, can have as many event users are you want - but an event user can only have one event generator.
You cannot get a list or count of all users connected to a generator except by iterating over the list.

### Declaration
``` c++
static int8_t get_user_channel_number(event::user::user_t event_user);
```

### Usage
```c++
int8_t connected_to = Event::get_user_channel_number(event::user::ccl0_event_a); // Returns the channel number ccl0_event_a is connected to
```


## get_user_channel()
Static function that returns the Event channel object a particular user is connected to. unlike get_user_channel_number()`, this returns a reference to an Event object, and returns a referece to the `Event_empty` object if not connected to any event channel.

### Declaration
``` c++
static Event& get_user_channel(event::user::user_t event_user);
```

### Usage
```c++
Event& myEvent = Event::get_user_channel(event::user::ccl0_event_a);
```


## set_user()
Function to connect an event user to an event generator. Note that a generator can have multiple users.

### Declaration
``` c++
void set_user(event::user::user_t event_user);
```

### Usage
```c++
Event0.set_generator(event::gen0::pin_pa0); // Set pin PA0` as event generator for Event0
Event0.set_user(event::user::evoutc);       // Set EVOUTC (pin PC2) as event user
Event0.set_user(event::user::evoutd);       // Set evoutD (pin PD2) as event user
```

### User table
Below is a table with all possible event users.
Note that `evoutN_pin_pN7` is the same as `evoutN_pin_pN2` but where the pin is swapped from 2 to 7. This means that for instance, `evouta_pin_pa2` can't be used in combination with `evouta_pin_pa7.`

| Event users                                     | Notes                                                                 |
|-------------------------------------------------|-----------------------------------------------------------------------|
| `event::user::ccl0_event_a`                     |                                                                       |
| `event::user::ccl0_event_b`                     |                                                                       |
| `event::user::ccl1_event_a`                     |                                                                       |
| `event::user::ccl1_event_b`                     |                                                                       |
| `event::user::ccl2_event_a`                     |                                                                       |
| `event::user::ccl2_event_b`                     |                                                                       |
| `event::user::ccl3_event_a`                     |                                                                       |
| `event::user::ccl3_event_b`                     |                                                                       |
| `event::user::adc0_start`                       |                                                                       |
| `event::user::evouta_pin_pa2`                   |                                                                       |
| `event::user::evouta_pin_pa7`                   | Pin swapped variant of `evouta_pin_pa2`                               |
| `event::user::evoutb_pin_pb2`                   | Only available on ATmegaX809                                          |
| `event::user::evoutc_pin_pc2`                   |                                                                       |
| `event::user::evoutc_pin_pc7`                   | Pin swapped variant of `evoutc_pin_pc2`. Only available on ATmegaX809 |
| `event::user::evoutd_pin_pd2`                   |                                                                       |
| `event::user::evoutd_pin_pd7`                   | Pin swapped variant of `evoutd_pin_pd2`                               |
| `event::user::evoute_pin_pe2`                   | Only available on ATmegaX809                                          |
| `event::user::evoutf_pin_pf2`                   | Not available on 28-pin parts                                         |
| `event::user::usart0_irda`                      |                                                                       |
| `event::user::usart1_irda`                      |                                                                       |
| `event::user::usart2_irda`                      |                                                                       |
| `event::user::usart3_irda`                      |                                                                       |
| `event::user::tca0` or `event::user::tca0_capt` |                                                                       |
| `event::user::tcb0` or `event::user::tcb0_capt` |                                                                       |
| `event::user::tcb1` or `event::user::tcb1_capt` |                                                                       |
| `event::user::tcb2` or `event::user::tcb2_capt` |                                                                       |
| `event::user::tcb3` or `event::user::tcb3_capt` |                                                                       |


## set_user_pin(uint8_t pin_number)
Function to set an Arduino pin as an event user. Note that only some pins can be used for this. See table below for more details

### Declaration
``` c++
int8_t set_user_pin(uint8_t pin_number);
```

### Usage
```c++
Event0.set_user_pin(PIN_PA2);
```

### Arduino pin table
| Event pin users | Notes                                                                                                    |
|-----------------|----------------------------------------------------------------------------------------------------------|
| PIN_PA2         |                                                                                                          |
| PIN_PA7         | Pin swapped variant of PIN_PA2. Cannot be used in combination with PIN_PA2                               |
| PIN_PB2         | Only available on ATmegaX809                                                                             |
| PIN_PC2         |                                                                                                          |
| PIN_PC7         | Pin swapped variant of PIN_PC2. Cannot be used in combination with PIN_PC2. Only available on ATmegaX809 |
| PIN_PD2         |                                                                                                          |
| PIN_PD7         | Pin swapped variant of PIN_PD2. Cannot be used in combination with PIN_PD2                               |
| PIN_PE2         | Only available on ATmegaX809                                                                             |
| PIN_PF2         | Not available on 28-pin parts                                                                            |


## clear_user()
Function to detach a user from a channel. Note that you don't need to know what channel to detach from, simply use `Event::clear_user()`.

### Declaration
``` c++
static void clear_user(event::user::user_t event_user);
```

### Usage
```c++
Event::clear_user(event::user::evouta); // Remove the event::user::evouta from whatever event channel it is connected to
```


## soft_event()
Creates a single software event - users connected to that channel will react to it in the same way as they would to one caused by the generator the channel is connected to.
Great if you have to force trigger something. Note that a software event only lasts a single system clock cycle, so it's rather fast!
The software events will invert the channel, and so will trigger something regardless of whether it needs a the event channel to go high or low.

### Declaration
``` c++
void soft_event();
```

### Usage
```c++
Event0.soft_event(); // Create a single software event on Event0
```


### long_soft_event()
`soft_event()` is only one system clock long, and might be difficult to catch in a real-life application. This function does the same thing as `soft_event()` but has a programmable interval for how long the soft event will last.

The event lengths that are available are 2, 4, 6, 10 and 16 system clocks. (Any number less than 4 will give 2 clock-long pulse, only 4 will give a 4 clock long one. Anything between 4 and 10 will give 6, exactly 10 will give 10, and anything larger will give 16).

#### Usage
```c++
Event0.long_soft_event(4);  // Will invert the state of the event channel for 4 system clock cycles (200ns at 20 MHz)
Event0.long_soft_event(10); // Will invert the state of the event channel for 10 system clock cycles (500ns at 20 MHz)

```
Don't forget that this is an invert, not a "high" or "low". It should be entirely possible for the event that normally drives it to occur resulting in the state changing during that pulse, depending on it's configuration. Note also that the overhead of long_soft_event is typically several times the length of the pulse due to calculating the bitmask to write; it's longer with higher numbered channels.


## start()
Starts an event generator channel by writing the generator selected by the `set_generator()` function.

### Declaration
``` c++
void start(bool state = true);
```

### Usage
```c++
Event0.start(); // Starts the Event0 generator channel
```


## stop()
Stops an event generator channel. The `Eventn` object retains memory of what generator it was previously set to.

### Declaration
``` c++
void stop();
```

### Usage
```c++
Event0.stop(); // Stops the Event0 generator channel
```


## gen_from_peripheral() and user_from_peripheral()
These two static functions allow you to pass a reference to a peripheral module, and get back the generator or user associated with it. In this context the "Peripheral Modules" are the structs containing the registers, defined in the io headers; for example `TCB0` or `USART1` or `CCL`.

This is most useful if you are writing portable (library) code that uses the Event library to interact with the event system. Say you made a library that lets users make one-shot pulses with timerB. You use the Event library to handle that part. You would of course need to know which timer to use - the natural way would be to ask the user to pass a reference or pointer.
But then what? The fact that you've got the pointer to something which, as it happens, is TCB0 (which itself is annoying to determine from an unknown pointer)... though even KNOWING THAT, you're not able to use it with the event library, since it needs event::user::tcb0 (or event::user::tcb0_capt). As the function names imply, one gives generators, the other gives users. They take 2 arguments, the first being a pointer to a peripheral struct.
The second, defaulting to 0, is the "type" of generator or user. Some peripherals have more than one event input or output. These are ordered in the same order as they are in the tables here and in the datasheet listings.

### Usage
```c
// Here we see a typical use case - you get the generator, and immediately ask Event to assign a channel to it and give that to you. After getting it, you test to make sure it's not Event_empty, which indicates that either gen_from_peripheral failed, or assign_generator was out of event channels. Either way that's probably the user's fault, so you decide to return an error code.
uint8_t init(TCB_t* some_timer, /*and more arguments, most likely */)
{
  &Event_TCBnCapt = Event::assign_generator(Event::gen_from_peripheral(some_timer, 0));
  if (_TCBnCapt.get_channel_number() == 255)
    return MY_ERROR_INVALID_TIMER_OR_NO_FREE_EVENT;
  doMoreCoolStuff();
}
```

Shown below, generators/user per instance  (second argument should be less than this; zero-indexed), and the number of instances (for reference)

| Peripheral |   mega0  |
|------------|----------|
| TCAn       | 5 / 1 x1 |
| TCBn       | 1/1 x3-4 |
| CCL *      | 4 / 8    |
| ACn        | 1 / 0 x1 |
| USARTn     | !/1 x3-4 |

`*` - There is only one CCL peripheral, with multiple logic blocks. Each logic block has 1 event generator and 2 event users. If using the logic library, get the Logic instance number. The output generator is that number. The input is twice that number, and twice that number + 1.
`!` - These parts do have an option, but we didn't bother to implement it because it isn't particularly useful. But the Event RX mode combined with the TX input to the CCL permit arbitrary remapping of RX and very flexible remapping of TX.

And what they are:

| Peripheral |   TCAn   | TCBn |  CCL*  | ACn | USARTn  |
|------------|----------|------|---------|-----|---------|
| gen 0      | OVF/LUNF | CAPT | LUT0OUT | OUT |    !    |
| gen 1      |     HUNF |      | LUT1OUT |     |         |
| gen 2      |     CMP0 |      | LUT2OUT |     |         |
| gen 3      |     CMP1 |      | LUT3OUT |     |         |
| gen 4      |     CMP2 |      |   ETC.  |     |         |
| user 0     |   EVACTA | CAPT | LUT0EVA |  -  | EVENTRX |
| user 1     |          |      | LUT0EVB |     |         |
| user 2     |          |      | LUT1EVA |     |         |
| user 3     |          |      | LUT1EVB |     |         |
| user 4     |          |      |   ETC.  |     |         |

`*` - Since there's only one CCL, the pointer (or rather, its type) is just used to select which implementation is used. But this does mean that the CCL can have an insane number of options. But that's fine, because there are plenty of numbers between 0 and 255.
`!` - These parts do have an option, but we didn't bother to implement it because it isn't particularly useful. But the Event RX mode combined with the TX input to the CCL permit arbitrary remapping of RX and very flexible remapping of TX!


Asking for a generator that doesn't exist will return 0 (disabled); be sure to check for this in some way. Asking for a user that doesn't exist will return 255, which the library is smart enough not to accept.

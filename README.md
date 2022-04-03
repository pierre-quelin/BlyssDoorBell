# 433MHz Blyss Door Bell

Project to hack a door bell to signal various events.

The origial receiver is a Conforama/Blyss door bell.
Emitter Ref. Unknown
Receiver Ref. DC6-FR-WH 656185-433.92MHz.

Tanks to Suat Özgür for the [rc-switch](https://github.com/sui77/rc-switch/) lib.

# Receiver (sniffer)

The 433MHz RF sniffer is only used to make a copy of the original code that is sent by the door bell.

## Hardware

- 1x ASK RF SRX882S module 433mhz receiver module
- 1x Leonardo / Arduino pro micro (Atmega 32u4) / Arduino mini pro (Atmega 328p)

## Software

# Transmitter

## Hardware

- 1x ASK RF STX882+ module 433mhz transmitter module
- 1x Leonardo / Arduino pro micro (Atmega 32u4) / Arduino mini pro (Atmega 328p)
- 1x Switch

## Software

To make the module autonomous, it is necessary that it consumes as little energy as possible. (cf. [low-power](https://www.arduino.cc/reference/en/libraries/low-power/))

The card will have to go into power down state until a wake up pin is activated that can bring it out of state.

The transmission module will then be activated.

A message will be sent.

The transmission module will then be deactivated and the card put back into power down state.

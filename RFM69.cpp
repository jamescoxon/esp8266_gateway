// RFM69.cpp
//
// Ported to Arduino 2014 James Coxon
//
// Copyright (C) 2014 Phil Crump
//
// Based on RF22 Copyright (C) 2011 Mike McCauley ported to mbed by Karl Zweimueller
// Based on RFM69 LowPowerLabs (https://github.com/LowPowerLab/RFM69/)


#include <SPI.h>
#include "RFM69.h"
#include "RFM69Config.h"

RFM69::RFM69()
{
    _mode = RFM69_MODE_RX;
}

boolean RFM69::init()
{
    _slaveSelectPin = 15;
    pinMode(_slaveSelectPin, OUTPUT); // Init nSS

    delay(100);

    SPI.setDataMode(SPI_MODE0);
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV2);
    SPI.begin();
    
    // Set up device
    for (uint8_t i = 0; CONFIG[i][0] != 255; i++)
        spiWrite(CONFIG[i][0], CONFIG[i][1]);
    
    setMode(_mode);

    // Clear TX/RX Buffer
    _bufLen = 0;
    
    if (spiRead(RFM69_REG_10_VERSION)==0x00)
    {
        // Zero version number, RFM probably not connected/functioning
        return false;
    }

    return true;
}

uint8_t RFM69::spiRead(uint8_t reg)
{
    digitalWrite(_slaveSelectPin, LOW);
    
    SPI.transfer(reg & ~RFM69_SPI_WRITE_MASK); // Send the address with the write mask off
    uint8_t val = SPI.transfer(0); // The written value is ignored, reg value is read
    
    digitalWrite(_slaveSelectPin, HIGH);
    return val;
}

void RFM69::spiWrite(uint8_t reg, uint8_t val)
{
    digitalWrite(_slaveSelectPin, LOW);
    
    SPI.transfer(reg | RFM69_SPI_WRITE_MASK); // Send the address with the write mask on
    SPI.transfer(val); // New value follows

    digitalWrite(_slaveSelectPin, HIGH);
}

void RFM69::spiBurstRead(uint8_t reg, uint8_t* dest, uint8_t len)
{
    digitalWrite(_slaveSelectPin, LOW);
    
    SPI.transfer(reg & ~RFM69_SPI_WRITE_MASK); // Send the start address with the write mask off
    while (len--)
        *dest++ = SPI.transfer(0);

    digitalWrite(_slaveSelectPin, HIGH);
}

void RFM69::spiBurstWrite(uint8_t reg, const uint8_t* src, uint8_t len)
{
    digitalWrite(_slaveSelectPin, LOW);
    
    SPI.transfer(reg | RFM69_SPI_WRITE_MASK); // Send the start address with the write mask on
    while (len--)
        SPI.transfer(*src++);
        
    digitalWrite(_slaveSelectPin, HIGH);
}

void RFM69::spiFifoWrite(const uint8_t* src, uint8_t len)
{
    digitalWrite(_slaveSelectPin, LOW);
    
    // Send the start address with the write mask on
    SPI.transfer(RFM69_REG_00_FIFO | RFM69_SPI_WRITE_MASK); // Send the start address with the write mask on
    // First byte is packet length
    SPI.transfer(len);
    // Then write the packet
    while (len--)
        SPI.transfer(*src++);
    	
    digitalWrite(_slaveSelectPin, HIGH);
}

void RFM69::setMode(uint8_t newMode)
{
    spiWrite(RFM69_REG_01_OPMODE, (spiRead(RFM69_REG_01_OPMODE) & 0xE3) | newMode);
    _mode = newMode;
}

uint8_t  RFM69::mode()
{
    return _mode;
}

boolean RFM69::checkRx()
{
    // Check IRQ register for payloadready flag (indicates RXed packet waiting in FIFO)
    if(spiRead(RFM69_REG_28_IRQ_FLAGS2) & RF_IRQFLAGS2_PAYLOADREADY) {
        // Get packet length from first byte of FIFO
        _bufLen = spiRead(RFM69_REG_00_FIFO)+1;
        // Read FIFO into our Buffer
        spiBurstRead(RFM69_REG_00_FIFO, _buf, RFM69_FIFO_SIZE);
        // Read RSSI register (should be of the packet? - TEST THIS)
        _lastRssi = -(spiRead(RFM69_REG_24_RSSI_VALUE)/2);
        // Clear the radio FIFO (found in HopeRF demo code)
        clearFifo();
        return true;
    }
    
    return false;
}

void RFM69::recv(uint8_t* buf, uint8_t* len)
{
    // Copy RX Buffer to byref Buffer
    memcpy(buf, _buf, _bufLen);
    *len = _bufLen;
    // Clear RX Buffer
    _bufLen = 0;
}

void RFM69::send(const uint8_t* data, uint8_t len, uint8_t power)
{
    // power is TX Power in dBmW (valid values are 2dBmW-20dBmW)
    if(power<2 or power >20) {
        // Could be dangerous, so let's check this
        return;
    }
    uint8_t oldMode = _mode;
    // Copy data into TX Buffer
    memcpy(_buf, data, len);
    // Update TX Buffer Size
    _bufLen = len;
    // Start Transmitter
    setMode(RFM69_MODE_TX);
    // Set up PA
    if(power<=17) {
        // Set PA Level
        uint8_t paLevel = power + 14;
	spiWrite(RFM69_REG_11_PA_LEVEL, RF_PALEVEL_PA0_OFF | RF_PALEVEL_PA1_ON | RF_PALEVEL_PA2_ON | paLevel);        
    } else {
        // Disable Over Current Protection
        spiWrite(RFM69_REG_13_OCP, RF_OCP_OFF);
        // Enable High Power Registers
        spiWrite(RFM69_REG_5A_TEST_PA1, 0x5D);
        spiWrite(RFM69_REG_5C_TEST_PA2, 0x7C);
        // Set PA Level
        uint8_t paLevel = power + 11;
	spiWrite(RFM69_REG_11_PA_LEVEL, RF_PALEVEL_PA0_OFF | RF_PALEVEL_PA1_ON | RF_PALEVEL_PA2_ON | paLevel);
    }
    // Wait for PA ramp-up
    while(!(spiRead(RFM69_REG_27_IRQ_FLAGS1) & RF_IRQFLAGS1_TXREADY)) { };
    // Throw Buffer into FIFO, packet transmission will start automatically
    spiFifoWrite(_buf, _bufLen);
    // Clear MCU TX Buffer
    _bufLen = 0;
    // Wait for packet to be sent
    while(!(spiRead(RFM69_REG_28_IRQ_FLAGS2) & RF_IRQFLAGS2_PACKETSENT)) { };
    // Return Transceiver to original mode
    setMode(oldMode);
    // If we were in high power, switch off High Power Registers
    if(power>17) {
        // Disable High Power Registers
        spiWrite(RFM69_REG_5A_TEST_PA1, 0x55);
        spiWrite(RFM69_REG_5C_TEST_PA2, 0x70);
        // Enable Over Current Protection
        spiWrite(RFM69_REG_13_OCP, RF_OCP_ON | RF_OCP_TRIM_95);
    }
}

void RFM69::SetLnaMode(uint8_t lnaMode) {
    // RF_TESTLNA_NORMAL (default)
    // RF_TESTLNA_SENSITIVE
    spiWrite(RFM69_REG_58_TEST_LNA, lnaMode);
}

void RFM69::clearFifo() {
    // Must only be called in RX Mode
    // Apparently this works... found in HopeRF demo code
    setMode(RFM69_MODE_STDBY);
    setMode(RFM69_MODE_RX);
}

float RFM69::readTemp()
{
    // Store current transceiver mode
    uint8_t oldMode = _mode;
    // Set mode into Standby (required for temperature measurement)
    setMode(RFM69_MODE_STDBY);
	
    // Trigger Temperature Measurement
    spiWrite(RFM69_REG_4E_TEMP1, RF_TEMP1_MEAS_START);
    // Check Temperature Measurement has started
    if(!(RF_TEMP1_MEAS_RUNNING && spiRead(RFM69_REG_4E_TEMP1))){
        return 255.0;
    }
    // Wait for Measurement to complete
    while(RF_TEMP1_MEAS_RUNNING && spiRead(RFM69_REG_4E_TEMP1)) { };
    // Read raw ADC value
    uint8_t rawTemp = spiRead(RFM69_REG_4F_TEMP2);
	
    // Set transceiver back to original mode
    setMode(oldMode);
    // Return processed temperature value
    return 168.3-float(rawTemp);
}

int16_t RFM69::lastRssi() {
    return _lastRssi;
}

int16_t RFM69::sampleRssi() {
    // Must only be called in RX mode
    if(_mode!=RFM69_MODE_RX) {
        // Not sure what happens otherwise, so check this
        return 0;
    }
    // Trigger RSSI Measurement
    spiWrite(RFM69_REG_23_RSSI_CONFIG, RF_RSSI_START);
    // Wait for Measurement to complete
    while(!(RF_RSSI_DONE && spiRead(RFM69_REG_23_RSSI_CONFIG))) { };
    // Read, store in _lastRssi and return RSSI Value
    _lastRssi = -(spiRead(RFM69_REG_24_RSSI_VALUE)/2);
    return _lastRssi;
}

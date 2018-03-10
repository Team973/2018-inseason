"""
Spew random-ish data to network tables so we can (partially) test GreyDash
without robot access
"""
import time
from networktables import NetworkTables
import random

NetworkTables.initialize()

sd = NetworkTables.getTable("SmartDashboard")

while True:
    sd.putNumber("misc/pdp/batteryvoltage", 12 + random.random())
    time.sleep(0.5)

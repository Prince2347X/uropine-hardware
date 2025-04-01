# v0 - Intial version of Uropine Device

<details>
<summary><span style="font-size: 1.2em;"><strong>Version Metadata</strong></span></summary>

| Metadata      | Value                   |
|---------------|-------------------------|
| Version       | 0.5.0                   |
| Release Date  | 2024-09-10              |
| Codename      | Prototype Alpha         |
| Status        | Deprecated              |

</details>

---

The Uropine device started from a basic prototype whose purpose was just to measure the bladder pressure and return the value on serial output.

### Apperance

Image

> **Properties**
> 
> | Property    | Value        |
> |-------------|--------------|
> | Shape       | Cuboidal     |
> | Color       | Black        |
> | Dimensions  | 200x90x60 mm |
> | Weight      |              |

### Components

- Arduino Uno
- Resistor(150ohm)
- Medical Grade Pressure Sensor
- Amplifier(AD620AN)
- Arduino Datecabel
- Zero PCB

### Circuit Diagram



### Limitations 
1. **Size** - The size of the device is big with unnecessary empty space inside it. It is also inconvinient for the patient to keep it attached at the level of bladder.
2. **Connectivity** - This version of the device was only compatible with wired connection to the Tab (for data visualization). This is making the device immobile for the doctors and nurses while performing the test on the patient.
3. **Water Vulnerability** - The device is not fully waterproof and the enclosure does not provide complete protection against water exposure. Since this device is tested in such an environment where chances of urine or saline getting into the device which could harm the electrical components inside.
4. **Poor enclosure material** - This is the very first prototype of the device, the material of enclosure is very poor.

----------------------------------------------------------

# v1 - Uropine Microcontroller

TBD

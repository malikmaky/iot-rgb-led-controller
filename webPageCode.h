const char webPageCode[] =
R"=====(
<!DOCTYPE html>
<html>
<head>
    <title>RGB LED Control</title>
    <style>
        body {
          margin: 10px;
          font-family: 'Trebuchet MS';
          text-align: center;
          background-color: #f4f4f4;
        }

        .container {
          max-width: 600px;
          margin: 50px auto;
          padding: 20px;
          background-color: #fff;
          border-radius: 8px;
          box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
          display: flex;
          flex-direction: column;
          align-items: center;
        }
        
        .row-container {
          width: 100%;
          margin-bottom: 20px;
          display: flex;
          justify-content: space-evenly;
        }
        
        h1 {
          font-family: 'Trebuchet MS';
          color: #9c4464;
        }

        .led {
          width: 40px;
          height: 40px;
          border-radius: 50%;
          background-color: #F00;
          box-shadow: rgba(0, 0, 0, 0.15) 0 0 10px,
                      inset rgba(0, 0, 0, 100) 0 0 5px, 
                      #F00 0 2px 5px 1px;
        }

        .color-picker {
          margin-top: 5px;
          padding-top: 2px;
          border: 1px solid #ccc;
          border-radius: 2px;
        }

        button{
          margin-right: 15px;
          padding: 5px 10px;
          min-width: 130px;
          height: 40px;
          font-family: 'Trebuchet MS';
          cursor: pointer;
          transition: all 0.3s ease;
          position: relative;
          display: inline-block;
          outline: none;
          border-radius: 5px;
          border: 2px solid #9c4464;
          background: #9c4464;
          color: #fff;
        }
        
        button:hover {
          background: #fff;
          color: #9c4464
        }
    </style>
</head>

<body>
    <div class="container">
      <!-- Header -->
      <h1>RGB LED Control</h1>
      <br>
      <div class="row-container">
        <!-- LED -->
        <div class="led"></div>
        <!-- Color Picker-->
        <input type="color" id="colorPicker" class="color-picker" value="#ff0000">
      </div>
      <br>
      
        <!-- Buttons -->
      <div class="row-container">
        <button onclick="turnOn()" >Turn On</button>
        <button onclick="turnOff()" >Turn Off</button>
      </div>
    </div>

    <script>
        const colorPicker = document.getElementById('colorPicker');
        const led = document.querySelector('.led');

        // Change LED color when color picker changes values
        colorPicker.addEventListener('input', function() {
            const color = colorPicker.value;
            updateLedColor(color);
        });

        function updateLedColor(color) {

            // Calculate HEX -> RGB
            const r = Math.floor(parseInt(color.substring(1, 3), 16));
            const g = Math.floor(parseInt(color.substring(3, 5), 16));
            const b = Math.floor(parseInt(color.substring(5, 7), 16));
            
            // Update LED background color
            led.style.backgroundColor = `rgb(${r}, ${g}, ${b})`;

            // Update LED box shadow
            led.style.boxShadow = `0 0 10px rgba(0, 0, 0, 0.15), inset 0 0 5px rgba(0, 0, 0, 100), 0 2px 5px 1px rgba(${r}, ${g}, ${b})`;
            
            colorPicker.value = color;
        }

        function turnOn() {
                    updateLedColor(colorPicker.value);
                    // Sends information regarding turning the led on and its color
                    connection.send("LED ON,"+colorPicker.value);
                    console.log("Led is turned on.");
        }

        function turnOff() {
                    led.style.backgroundColor = '#fff';
                    led.style.boxShadow = `0 0 10px rgba(0, 0, 0, 0.15), inset 0 0 5px #fff, 0 2px 5px 1px #fff`;
                    // Sends information regarding turning the led off
                    connection.send("LED OFF");
                    console.log("Led is turned off.");
        }
        
        // Connection between client and the NodeMCU
        var connection = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);
        
        // When first connected
        connection.onopen = function (){ connection.send('Connect ' + new Date()); };

        // When a message is received
        connection.onmessage = function (e){
            console.log('Server: ', e.data);

            if (e.data.startsWith("LED ON")) { // If LED is turned on
                
                const parts = e.data.split(',');

                // Color in HEX form
                const color = parts[1];

                // Update the color
                updateLedColor(color);
                console.log("Led is turned on with color:", color);
                
            }else if (e.data === "LED OFF") { // If LED is turned off
                led.style.backgroundColor = '#fff';
                led.style.boxShadow = `0 0 10px rgba(0, 0, 0, 0.15), inset 0 0 5px #fff, 0 2px 5px 1px #fff`;
            }
        };
        
        // When a WebSocket error comes up
        connection.onerror = function (error) { console.log('WebSocket Error ', error);};
    </script>
</body>
</html>
)=====";
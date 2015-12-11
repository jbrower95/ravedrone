document.addEventListener('deviceready', function() { app.initialize() }, false);

var app = {};

app.RBL_SERVICE_UUID = '713d0000-503e-4c75-ba94-3148f18d941e';
app.RBL_CHAR_TX_UUID = '713d0002-503e-4c75-ba94-3148f18d941e';
app.RBL_CHAR_RX_UUID = '713d0003-503e-4c75-ba94-3148f18d941e';
app.RBL_TX_UUID_DESCRIPTOR = '00002902-0000-1000-8000-00805f9b34fb';

app.initialize = function()
{
    app.connected = false;
};

app.sendMessage = function(val)
{
    if (app.connected)
    {
        function onMessageSendSuccess()
        {
            if (val == 0) {
                app.setLandingState();
            }
        };

        function onMessageSendFailure(errorCode)
        {
            // Disconnect and show an error message to the user.
            app.disconnect('Disconnected');

            // Write debug information to console
            console.log('Error - No device connected.');
        };
        // Convert message
        var data = new Uint8Array([val]);

        app.device.writeCharacteristic(
            app.RBL_CHAR_RX_UUID,
            data,
            onMessageSendSuccess,
            onMessageSendFailure
        );
    }
    else
    {
        // Disconnect and show an error message to the user.
        app.disconnect('Disconnected');

        // Write debug information to console
        console.log('Error - No device connected.');
    }
};

app.setLandingState = function() {
    $("#controlView").hide();
    $("#landingView").show();
    $("#startView").show();
}

app.setLoadingLabel = function(message)
{
    console.log(message);
    $('#loadingStatus').text(message);
};

app.connectTo = function(address)
{
    device = app.devices[address];

    $('#loadingView').css('display', 'table');

    app.setLoadingLabel('Trying to connect to ' + device.name);

    function onConnectSuccess(device)
    {

        function onServiceSuccess(device)
        {
            // Application is now connected
            app.connected = true;
            app.device = device;

            console.log('Connected to ' + device.name);

            device.writeDescriptor(
                app.RBL_CHAR_TX_UUID, // Characteristic for accelerometer data
                app.RBL_TX_UUID_DESCRIPTOR, // Configuration descriptor
                new Uint8Array([1,0]),
                function()
                {
                    console.log('Status: writeDescriptor ok.');

                    $('#loadingView').hide();
                    $('#scanResultView').hide();
                    $('#landingView').hide();
                    $('#controlView').show();
                },
                function(errorCode)
                {
                    // Disconnect and give user feedback.
                    app.disconnect('Failed to set descriptor.');

                    // Write debug information to console.
                    console.log('Error: writeDescriptor: ' + errorCode + '.');
                }
            );

            function failedToEnableNotification(erroCode)
            {
                console.log('BLE enableNotification error: ' + errorCode);
            };

            device.enableNotification(
                app.RBL_CHAR_TX_UUID,
                app.receivedMessage,
                function(errorcode)
                {
                    console.log('BLE enableNotification error: ' + errorCode);
                }
            );

            $('#scanResultView').hide();
            $('#landingView').hide();
            $('#controlView').show();
        }

        function onServiceFailure(errorCode)
        {
            // Disconnect and show an error message to the user.
            app.disconnect('Device is not from RedBearLab');

            // Write debug information to console.
            console.log('Error reading services: ' + errorCode);
        }

        app.setLoadingLabel('Identifying services...');

        // Connect to the appropriate BLE service
        device.readServices(
            [app.RBL_SERVICE_UUID],
            onServiceSuccess,
            onServiceFailure
        );
    }

    function onConnectFailure(errorCode)
    {
        app.disconnect('Disconnected from device');

        // Show an error message to the user
        console.log('Error ' + errorCode);
    }

    // Stop scanning
    evothings.easyble.stopScan();

    // Connect to our device
    console.log('Identifying service for communication');
    device.connect(onConnectSuccess, onConnectFailure);
};

app.startScan = function()
{
    app.disconnect();

    console.log('Scanning started...');

    app.devices = {};

    var htmlString =
        '<img src="img/loader_small.gif" style="display:inline; vertical-align:middle">' +
        '<p style="display:inline">   Scanning...</p>';

    $('#scanResultView').append($(htmlString));

    $('#scanResultView').show();

    function onScanSuccess(device)
    {
        if (device.name != null)
        {
            app.devices[device.address] = device;

            console.log('Found: ' + device.name + ', ' + device.address + ', ' + device.rssi);

            var htmlString =
                '<div class="deviceContainer" onclick="app.connectTo(\'' +
                device.address + '\')">' +
                '<p class="deviceName">' + device.name + '</p>' +
                '<p class="deviceAddress">' + device.address + '</p>' +
                '</div>';

            $('#scanResultView').append($(htmlString));
        }
    };

    function onScanFailure(errorCode)
    {
        // Show an error message to the user
        app.disconnect('Failed to scan for devices.');

        // Write debug information to console.
        console.log('Error ' + errorCode);
    };

    evothings.easyble.reportDeviceOnce(true);
    evothings.easyble.startScan(onScanSuccess, onScanFailure);

    $('#startView').hide();
};

app.receivedMessage = function(data)
{
    if (app.connected)
    {
        // Convert data to String
        var message = String.fromCharCode.apply(null, new Uint8Array(data));
        
        // Update conversation
        app.updateThresholdValue(message);
    }
    else
    {
        // Disconnect and show an error message to the user.
        app.disconnect('Disconnected');

        // Write debug information to console
        console.log('Error - No device connected.');
    }
};

app.updateThresholdValue = function(value) {
    if (isNaN(parseInt(value))) {
        alert("Error: Got a non-number response from arduino: " + value)
    } else {
        $(".thresholdValue").text(value);
    }

}

app.disconnect = function(errorMessage)
{
    if (errorMessage)
    {
        navigator.notification.alert(errorMessage, function() {});
    }

    app.connected = false;
    app.device = null;

    // Stop any ongoing scan and close devices.
    evothings.easyble.stopScan();
    evothings.easyble.closeConnectedDevices();

    console.log('Disconnected');

    $('#loadingView').hide();
    $('#scanResultView').hide();
    $('#scanResultView').empty();
    $('#controlView').hide();
    $('#landingView').hide();

    $('#startView').show();
};

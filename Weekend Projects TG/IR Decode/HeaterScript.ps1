$port= new-Object System.IO.Ports.SerialPort COM4,9600,None,8,one
$port.ReadTimeout = 9000
$port.DtrEnable = "true"
$port.open()
Start-Sleep 5
$port.Write("POWER")
Start-Sleep 5
$port.Close()
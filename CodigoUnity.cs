using UnityEngine;
using System.IO.Ports;

public class ControlBrazoSuperior : MonoBehaviour
{
    SerialPort arduino;
    public string nombrePuerto = "COM3";
    public int velocidadBaudios = 9600;
    public float velocidadRotacion = 120f;

    void Start()
    {
        try
        {
            arduino = new SerialPort(nombrePuerto, velocidadBaudios);
            arduino.ReadTimeout = 50;
            arduino.Open();
        }
        catch (System.Exception e)
        {
            Debug.LogError("❌ No se pudo abrir el puerto: " + e.Message);
        }
    }

    void Update()
    {
        if (arduino != null && arduino.IsOpen)
        {
            try
            {
                string data = arduino.ReadLine().Trim(); // ejemplo: "1,120"
                string[] partes = data.Split(',');

                if (partes.Length != 2)
                    return;

                int direccion = int.Parse(partes[0]);   // 1, -1, 0
                int velocidad = int.Parse(partes[1]);   // 0 a 255

                if (direccion != 0 && velocidad > 0)
                {
                    float rotacion = direccion * (velocidad / 255f) * velocidadRotacion;
                    transform.Rotate(Vector3.up, rotacion * Time.deltaTime);
                }
            }
            catch { }
        }
    }

    void OnApplicationQuit()
    {
        if (arduino != null && arduino.IsOpen)
        {
            arduino.Close();
        }
    }
}

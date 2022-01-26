#include <CircularBuffer.h>;
#include "Accel.h";
#include "interrupt.h";
#include "OLED.h";
#include "reconocimiento.h";
#include "filtrado.h";

//-----------declaración de variables

extern int totalInterruptCounter;
extern MPU9250_asukiaaa mySensor;

sensorData dataSensor;

CircularBuffer<int,200> HighPass_AcelX;
CircularBuffer<int,200> LowPass_AcelX;

CircularBuffer<int,200> HighPass_AcelY;
CircularBuffer<int,200> LowPass_AcelY;

CircularBuffer<int,200> HighPass_AcelZ;
CircularBuffer<int,200> LowPass_AcelZ;

CircularBuffer<int,200> HighPass_Total;

using index_t = decltype(HighPass_AcelX)::index_t;

int arraySize = 200;

int energia = 0;

int numeroPicos = 0;

int tiempoActualPico = 0;
int tiempoAnteriorPico = 0;

int tiempoEntrePicos = 0;

int mediaTiempos = 0;

int desTyp = 0;

int var = 0;

int total = 0;

int aX_1 = 0;
int aY_1 = 0;
int aZ_1 = 0;

int aX_2 = 0;
int aY_2 = 0;
int aZ_2 = 0;

int meanX = 0;
int meanY = 0;

int meanX_1 = 0;
int meanX_2 = 0;

int picoActual = 0;
int picoAnterior = 0;
int tiempoMax = 0;

int tiempos[] = {0};

//threshold para descartar
int thres_EnPico = 3000;
int thresholdTiempoZancada = 200;

//threshold para el reconocimiento
int thres_En1 = 100000;
int thres_En2 = 400000;
int thres_nPicos = 3;

int Actividad = 0;
int actAnterior = 0;

int frecuency = 50;

int contador = 0;

//filtrado
double ALPHA = 0.6;

//SETUP
void setup() {

  Serial.begin(115200);

// 1 digito -> acelerometro
// 2 digito -> magnetómetro
// 3 digito -> giroscopio
  sensorSetup(1,1,1);

//--------------inicializacion de la pantalla OLED
  OLEDsetup();

//--------------inicialización de la interrupción del timer a una frecuencia determinada
  timerInterruptSetup(frecuency);

//--------------antes de empezar el bucle principal lleno el array de datos

  while(!LowPass_AcelX.isFull()){  

    if(timerInterruptOn()){ 
  
    dataSensor = readAcel();
    
    aX_2 = aX_1;
    aY_2 = aY_1;
    aZ_2 = aZ_1;

    aX_1 = dataSensor.aX;
    aY_1 = dataSensor.aY;
    aZ_1 = dataSensor.aZ;

      if(totalInterruptCounter > 1){
        
      LowPass_AcelX.push(LowPass(aX_1,aX_2, ALPHA));
      HighPass_AcelX.push(HighPass(aX_1,LowPass_AcelX[200]));
  
      LowPass_AcelY.push(LowPass(aY_1,aY_2, ALPHA));
      HighPass_AcelY.push(HighPass(aY_1,LowPass_AcelY[200]));
  
      LowPass_AcelZ.push(LowPass(aZ_1,aZ_2, ALPHA));
      HighPass_AcelZ.push(HighPass(aZ_1,LowPass_AcelZ[200]));
    
    total = abs(HighPass_AcelX[200]) + abs(HighPass_AcelY[200]) + abs(HighPass_AcelZ[200]);
  
      }
    }
  }
}//END SETUP



void loop() {

   

  if(timerInterruptOn()){

    //--------------leo aceleraciones del sensor
    dataSensor = readAcel();

    //--------------Actualizo los valores de aceleración anteriores
    aX_2 = aX_1;
    aY_2 = aY_1;
    aZ_2 = aZ_1;
    //--------------asigno los valores actuales de aceleración
    aX_1 = dataSensor.aX;
    aY_1 = dataSensor.aY;
    aZ_1 = dataSensor.aZ;

    //--------------realizo el filtrado de las 3 axis de la aceleración, tanto paso alto como paso alto. 
    //--------------Para el paso alto se utiliza el paso bajo
    LowPass_AcelX.push(LowPass(aX_1,aX_2, ALPHA));
    HighPass_AcelX.push(HighPass(aX_1,LowPass_AcelX[200]));

    LowPass_AcelY.push(LowPass(aY_1,aY_2, ALPHA));
    HighPass_AcelY.push(HighPass(aY_1,LowPass_AcelY[200]));

    LowPass_AcelZ.push(LowPass(aZ_1,aZ_2, ALPHA));
    HighPass_AcelZ.push(HighPass(aZ_1,LowPass_AcelZ[200]));

    //--------------sumo los valores absolutos de las 3 axis
    total = abs(HighPass_AcelX[200]) + abs(HighPass_AcelY[200]) + abs(HighPass_AcelZ[200]);

    
    //--------------realizo un filtrado para la suma total y lo guardo en el array
    if (total < thres_EnPico)
    {
      HighPass_Total.push(0);
    }
    else
    {
      HighPass_Total.push(total);
    }
    
    //--------------cada 50 interrupciones se realiza el reconocimiento (50 interaciones / 50Hz = 1 seg)
    if(totalInterruptCounter%50 == 1){

        //--------------recorro el array entero para analizar la totalidad de los datos
        for(index_t i = 0; i < HighPass_Total.size(); i++) {

          //--------------sumo la energia total del vector
          energia = energia + HighPass_Total[i];

          //--------------contador dado que no puedo utilizar la variable i dado que es un tipo exclusivo para el circular buffer
          contador = contador + 1;

          //--------------obtengo las medias de las axis Y e X fuera de la función de reconocimiento dado que no me deja meter el vector en la función (no es array como tal)
          //--------------Ahora se suman los valores, despues se divide para todos lo valores
          meanY = meanY + LowPass_AcelY[i];

          //--------------defino una media para la primera mitad y otra para la segunda mitad (característica para el reconocimiento)
          if (i < 100)
          {
            meanX_1 = meanX_1 + LowPass_AcelX[i];
          }
          else
          {
            meanX_2 = meanX_2 + LowPass_AcelX[i];
          }

            //--------------Funcionalidad para contar el número de picos, 
            if(HighPass_Total[i] > thres_EnPico){

              //--------------defino con 1 o 0 si hay pico o no en esta iteración
              picoActual = 1;

              //--------------De esta forma puedo contabilizar en ms los tiempos
              tiempoActualPico = contador*(1000/frecuency);

              //--------------calculo la diferencia de tiempos con el pico anterior
              tiempoEntrePicos = tiempoActualPico - tiempoAnteriorPico;

              //--------------Si en el momento anterior no ha habido pico y el tiempo entre picos es mayor al definido
              if (picoAnterior == 0 && tiempoEntrePicos > thresholdTiempoZancada)
              {

                if (tiempoMax < tiempoEntrePicos)
                {
                tiempoMax = tiempoEntrePicos;
                }
              
                mediaTiempos = mediaTiempos + tiempoEntrePicos;
  
                tiempos[numeroPicos] = tiempoEntrePicos;
  
                numeroPicos = numeroPicos + 1;
  
                tiempoAnteriorPico = contador*(1000/frecuency);
              }              
            }            
            picoAnterior = picoActual;           
            picoActual = 0;           
        }
        
        //--------------se divide para el total correspondiente
        meanX_1 = meanX_1/(arraySize/2);
        meanX_2 = meanX_2/(arraySize/2);

        meanY = meanY/arraySize;

        
        //--------------Función de reconocimiento de actividad
        Actividad = reconocimiento(actAnterior,meanX_1,meanX_2,meanY,arraySize,energia,thres_En1,thres_En2,numeroPicos,thres_nPicos);
        
        //--------------Pantalla oled
        if (Actividad != actAnterior){
        printStatusOLED(Actividad);
        }      

        //--------------funcionalidades no utilizadas

//        mediaTiempos = mediaTiempos/numeroPicos;
//        
//        //verificar que los tiempos entre picos es aprox similar
//
//        for(i = 0; i < numeroPicos; i++){
//
//          var = (tiempoEntrePicos[i] - mediaTiempos);
//          
//        }
//
//        desTyp = sqrt(var / numeroPicos);



        //--------------inicialización de las variables 

        actAnterior = Actividad;

        energia = 0;

        numeroPicos = 0;
    
        tiempoActualPico = 0;
        
        tiempoAnteriorPico = 0;
        
        tiempoEntrePicos = 0;
        
        mediaTiempos = 0;

        contador = 0;
        
        
    }
  }
}

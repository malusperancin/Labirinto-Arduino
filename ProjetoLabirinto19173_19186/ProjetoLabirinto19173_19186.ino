//Giovanna Pavani Martelli 19173  data: 29/10/2019
//Maria Luiza Sperancin Mancebo 19186

#include <SoftwareSerial.h> //biblioteca do bluetooth
SoftwareSerial mySerial(2,3);//RX, TX

#include <Servo.h> //incluindo biblioteca do servo
Servo servoX; //declarando o servo x
Servo servoY; //declarando o servo y

 //declaracao de variaveis auxiliares
String dados;// dados capturados através do bluetooth
int x; // armazenamento da qtd de graus para o servoX
int y; // armazenamento da qtd de graus para o servoY

void setup() {
Serial.begin(9600); //inicia o serial
mySerial.begin(9600); //inicia o serial do bluetooth

servoX.attach(6); //inicia os servos
servoY.attach(7);
}

void loop()
{
  if (mySerial.available()) //se o serial estiver disponível
  {
    dados = mySerial.read(); //le o primeiro dado passado pelo bluetooth (X)
    x = tratarDados(dados); //trata o dado lido
    Serial.print(x);//printa no serial
    delay(70);

    dados = mySerial.read(); //le o segundo dado passado pelo bluetooth (Y)
    y = tratarDados(dados); //trata o dado lido
    Serial.println(y); //printa no serial
    delay(70);

    x = map(x, -10, 10, 5, 175); //faz regra de 3 entre o numero passado pelo bluetooth e os graus que serão executados no servo motor X - múmeros alterados por conta do mau funcionamento de um dos servos
    y = map(y, -10, 10, 180, 0); //faz regra de 3 entre o numero passado pelo bluetooth e os graus que serão executados no servo motor Y - fizemos o inverso aqui por causa da posição do servo na montagem

    delay(100);

    servoX.write(x); //o servo X gira a quantidade de graus da regra de 3 do X
    servoY.write(y); //o servo Y gira a quantidade de graus da regra de 3 do Y
  }
}

int tratarDados(String dados) //passa como parametro o numero que queremos tratar
{                              //alem de transformar o dado em int, tendo em vista que o app para android envia o dado em 1 byte, não possui numeros negativos,
  int ret = dados.toInt();     //então transformamos o número enviado em seu respectivo numero negativo
  if(ret == 255)
    ret = -1;
  if(ret == 254)
    ret = -2;
  if(ret == 253)
    ret = -3;
  if(ret == 252)
    ret = -4;
  if(ret == 251)
    ret = -5;
  if(ret == 250)
    ret = -6;
  if(ret == 249)
    ret = -7;
  if(ret == 248)
    ret = -8;
  if(ret == 247 || ret == 246)
    ret = -9;

  return ret; //retorna o numero encontrado
}

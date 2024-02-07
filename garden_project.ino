// 必要なライブラリのインクルード
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

// ソフトウェアシリアルの設定。IOピン10をRX, IOピン11をTXとして使用
SoftwareSerial mySoftwareSerial(10, 11);
DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
int buttonPin = 2; // ボタンが接続されているピン番号


void setup() {
  // ソフトウェアシリアルの開始。通信速度は9600bps
  mySoftwareSerial.begin(9600);
  // Arduinoのシリアル通信の開始。通信速度は9600bps
  Serial.begin(9600);

  // シリアルモニターにメッセージを表示
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  // DFPlayer Miniの初期化。初期化が成功しない場合はエラーメッセージを表示
  if (!myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true) {
      delay(0); // ESP8266のウォッチドッグタイマーに対応するためのコード
    }
  }
  // 初期化が成功した場合のメッセージ
  Serial.println(F("DFPlayer Mini online."));

  // DFPlayer Miniのボリュームを設定（0から30の範囲）
  myDFPlayer.volume(13);

  // ボタンピンを入力として設定し、プルアップ抵抗を有効化
  pinMode(buttonPin, INPUT_PULLUP); 
}

void loop() {
  // ボタンが押されたか確認
  if (digitalRead(buttonPin) == LOW) {
    myDFPlayer.play(1);  // タクトスイッチが押されたら、音声を再生
    delay(500);  // チャタリング防止のためのディレイ
  }
}

void printDetail(uint8_t type, int value) {
  // この関数は現在使用されていませんが、DFPlayer Miniからの詳細な情報を
  // 処理するために使用することができます。
}

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <time.h>
#include <TimeLib.h>
#include <HTTPClient.h>
#include <MySQL.h>
#include <string.h>
#include <WiFi.h>



//informacao do banco
char ip[] = "ipsecreto";
char table[] = "tabela";
char user_db[] = "usuario";
char password_db[] = "senha";
char db[] = "banco";


//cursores
char vendas[] = "SELECT x FROM y WHERE x IS NOT NULL AND y != ''";
char sum[] = "SELECT SUM(z) FROM y";





//display lcd
int lcdColumns = 16;
int lcdRows = 2;
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);


//wifi
char ssid[] = "ssid";
char password[] = "pass";


//endereço da API
char server_address[] = "api";


//iniciando http e wifi
HTTPClient http;
WiFiClient wifi;

//inicialização do banco
#define MAX_QUERY_LEN 128
MySQL sql(&wifi, ip, 3306);

//frases do dia
String frasesDoDia[] = {
  "Ame a vida.",
  "Seja gentil.",
  "Persista!",
  "Aprenda sempre.",
  "Espalhe amor.",
  "Sorria muito.",
  "Faca o bem.",
  "Seja grato.",
  "Viva feliz.",
  "Aja com fe.",
  "Sonhe alto.",
  "Celebre hoje.",
  "Desperte alegria.",
  "Viva intensamente.",
  "Supere desafios.",
  "Cultive otimismo.",
  "Brilhe como o sol.",
  "Acredite em você.",
  "Enfrente medos.",
  "Inspire confiança.",
  "Mantenha a calma.",
  "Semeie bondade.",
  "Colha gratidao.",
  "Seja luz.",
  "Voe alto.",
  "Escolha a paz.",
  "Abrace a felicidade.",
  "Valorize cada instante.",
  "Pratique a gratidao.",
  "Conquiste seus sonhos.",
  "Viva com propósito.",
  "Seja resiliente.",
  "Crie oportunidades.",
  "Cultive amizades.",
  "Aprenda com a vida.",
  "Agradeça sempre.",
  "Abrace o novo.",
  "Respire fundo.",
  "Aprecie a jornada.",
  "Cultive a serenidade.",
  "Abrace desafios.",
  "Ame incondicionalmente.",
  "Faça a diferença.",
  "Dance na chuva.",
  "Valorize o presente.",
  "Busque o equilíbrio.",
  "Acredite em seus sonhos.",
  "Cultive a alegria.",
  "Desperte seu potencial.",
  "Viva com autenticidade.",
  "Transforme desafios em oportunidades.",
  "Abra seu coracao.",
  "Aprecie as pequenas coisas.",
  "Seja a mudanca.",
  "Construa pontes.",
  "Respeite a natureza.",
  "Mantenha a mente aberta.",
  "Comemore conquistas.",
  "Pratique o desapego.",
  "Abra as asas.",
  "Abrace a simplicidade.",
  "Explore o desconhecido.",
  "Celebre a vida.",
  "Cultive a compaixao.",
  "Seja humilde.",
  "Inspire-se na natureza.",
  "Viva com amor.",
  "Valorize sua jornada.",
  "Aprenda com os erros.",
  "Cultive boas energias.",
  "Ame sem medidas.",
  "Desperte seu potencial.",
  "Abrace o aprendizado.",
  "Celebre suas conquistas.",
  "Acredite na magia.",
  "Deixe sua luz brilhar.",
  "Cultive a paciencia.",
  "Viva com coragem.",
  "Descubra sua forca.",
  "Seja autentico.",
  "Ame a si mesmo.",
  "Dedique tempo ao descanso.",
  "Mantenha a fe.",
  "Pratique a generosidade.",
  "Aprenda com a sabedoria.",
  "Valorize sua essencia.",
  "Desperte sua criatividade.",
  "Abrace a positividade.",
  "Crie momentos especiais.",
  "Siga seu coracao.",
  "Celebre cada dia.",
  "Viva em harmonia.",
  "Ame sem reservas.",
  "Cultive a gratidao.",
  "Desperte sua paixao.",
  "Acredite em seus talentos.",
  "Sorria para a vida.",
  "Abra portas.",
  "Valorize suas escolhas.",
  "Viva com plenitude.",
  "Cultive relacionamentos saudaveis.",
  "Seja a melhor versao de si mesmo.",
  "Abrace a jornada.",
  "Dance ao ritmo da vida.",
  "Viva o presente.",
  "Inspire confianca.",
  "Aprenda com a adversidade.",
  "Seja flexivel.",
  "Abrace a liberdade.",
  "Celebre sua autenticidade.",
  "Desperte seu entusiasmo.",
  "Viva com compaixao.",
  "Ame intensamente.",
  "Cultive a paz interior.",
  "Seja grato por tudo.",
  "Sorria para o mundo.",
  "Acredite em seu potencial.",
  "Viva com propósito.",
  "Abrace o amor.",
  "Celebre a diversidade.",
  "Cultive a honestidade.",
  "Ame a si mesmo.",
  "Desperte sua criatividade.",
  "Abrace a serenidade.",
  "Viva com paixao.",
  "Inspire o mundo.",
  "Aprenda com a experiencia.",
  "Seja resiliente.",
  "Cultive a gratidao.",
  "Ame a natureza.",
  "Desperte sua intuicao.",
  "Celebre a vida.",
  "Viva com leveza.",
  "Acredite em si mesmo.",
  "Sorria para a vida.",
  "Abrace a felicidade.",
  "Cultive a humildade.",
  "Seja grato por cada dia.",
  "Ame sem medidas.",
  "Desperte sua coragem.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
  "Abrace a felicidade.",
  "Cultive a gratidao.",
  "Desperte a criatividade.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
  "Abrace a felicidade.",
  "Cultive a gratidao.",
  "Desperte a criatividade.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
  "Abrace a felicidade.",
  "Cultive a gratidao.",
  "Desperte a criatividade.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
  "Abrace a felicidade.",
  "Cultive a gratidao.",
  "Desperte a criatividade.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
  "Abrace a felicidade.",
  "Cultive a gratidao.",
  "Desperte a criatividade.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
  "Abrace a felicidade.",
  "Cultive a gratidao.",
  "Desperte a criatividade.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
  "Abrace a felicidade.",
  "Cultive a gratidao.",
  "Desperte a criatividade.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
  "Abrace a felicidade.",
  "Cultive a gratidao.",
  "Desperte a criatividade.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
  "Abrace a felicidade.",
  "Cultive a gratidao.",
  "Desperte a criatividade.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
  "Abrace a felicidade.",
  "Cultive a gratidao.",
  "Desperte a criatividade.",
  "Celebre suas conquistas.",
  "Viva com autenticidade.",
  "Acredite em seus sonhos.",
  "Sorria para o futuro.",
  "Ame o presente.",
  "Desperte a alegria.",
  "Celebre o amor.",
  "Cultive a esperanca.",
  "Viva com compaixao.",
  "Abrace a generosidade.",
  "Ame a si mesmo.",
  "Desperte sua paixao.",
  "Celebre a vida.",
  "Viva com plenitude.",
  "Acredite em seu potencial.",
  "Sorria para o mundo.",
};
//execucao do query 
bool queryExecute(DataQuery_t& data, const char* queryStr, ...) {
  if (sql.connected()) {
    char buf[MAX_QUERY_LEN];
    va_list args;
    va_start (args, queryStr);
    vsnprintf (buf, sizeof(buf), queryStr, args);
    va_end (args);

    Serial.printf("Executing SQL query: %s\n", buf);
    return sql.query(data, buf);
  }
  return false;
}
//setup
void setup() {

  Serial.begin(115200);
  while (!Serial); 

lcd.init();
lcd.backlight();

delay(1000);
lcd.print("conectando wifi...");
WiFi.begin(ssid, password);
delay(1000);
while (WiFi.status() != WL_CONNECTED) {
  delay(3000);
  lcd.setCursor(0,0);
  lcd.print("erro wifi");
  lcd.setCursor(0,1);
  lcd.print("reconectando...");
  Serial.print(".");
  lcd.clear();

  }
delay(1000);
//conectando ao db
if (sql.connect(user_db, password_db, db)) {
    Serial.println();
  }
delay(2000);

//ajustando npt
lcd.setCursor(0,0);
lcd.print("ajustando tempo...");
configTime(0, 0, "pool.ntp.org");
delay(2000);
lcd.clear();
lcd.print("AGUARDANDO");
lcd.setCursor(0,1);
lcd.print("REQUISICAO");
lcd.setCursor(0,0);
}

//loop
void loop() {

  //requisicao GET
  http.begin(server_address);
  int httpCode = http.GET();


  //manter conexao aberta enquanto o dispositivo estiver ligado
  if(sql.connected() == false){
    sql.connect(user_db, password_db, db);
    delay(5000);
  }

//verificar codigo de resposta 
  if (httpCode > 0) {
    
  //se retornar 200 pode prosseguir
    if (httpCode == HTTP_CODE_OK) {
      
//pegar o dado da api
      String response = http.getString();
      lcd.clear();

    
      //verificar corpo da api e retornar função baseada nisso se a resposta for 200.
  if (response.indexOf("\"acumulado\":\"dinheiro\"") != -1) {
      soma();
      }

  if (response.indexOf("\"meta\":\"metadiaria\"") != -1) {
      rotina();
  }

  if (response.indexOf("\"temp\":\"temperatura\"") != -1) {
      meteorologia();
  }

  if (response.indexOf("\"frase\":\"frasedodia\"") != -1) {
      frase_do_dia();
  }

  if (response.indexOf("\"venda\":\"ultima\"") != -1) {
      ultima_venda();
  }
//logar a resposta
  Serial.println("Resposta:");
  Serial.println(response);

//se nao encontrar me mostre o erro
    } else {
      Serial.print("Erro na solicitação. Código de status: ");
      Serial.println(httpCode);
      String response_error = http.getString();
      Serial.println(response_error);
    }
  } else {
    Serial.println("Erro ao se conectar ao servidor.");
    Serial.println(httpCode);
  }
  http.end();
  delay(2000);

}

//funcao para retornar a frase do dia baseado no dia que estamos no ano 365 frases
void frase_do_dia() {
  time_t now = time(nullptr);
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);

  int dias = (timeinfo.tm_mon + 1) * 30 + timeinfo.tm_mday;

  int indice = dias % (sizeof(frasesDoDia) / sizeof(frasesDoDia[0]));
  lcd.setCursor(0, 0);

  String frase = frasesDoDia[indice];
    if (frase.length() <= 16) {
      lcd.print(frase);
    } else if (frase.length() <= 32) {
      lcd.print(frase.substring(0, 16));
      lcd.setCursor(0, 1);
      lcd.print(frase.substring(16));
    } else {
      lcd.print("bom dia");
    }
    
    delay(23);
  } 

//retornar a meta diaria do que vou fazer no dia 
void rotina() {
    time_t now = time(nullptr);
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);

  //ajustando o tempo para gmt do brasil 
    if (timeinfo.tm_hour >= 3) {
        timeinfo.tm_hour -= 3;
    } else {
        timeinfo.tm_hour = 24 + timeinfo.tm_hour - 3;
    }

    char data[11];
    strftime(data, sizeof(data), "%d/%m/%Y", &timeinfo);

    char horario[9];
    strftime(horario, sizeof(horario), "%H:%M:%S", &timeinfo);

    lcd.setCursor(0,0);
    lcd.print("Meta diária:");

    int hora = timeinfo.tm_hour;
    int minuto = timeinfo.tm_min;

    lcd.setCursor(0, 1);

    if (hora >= 6 && hora < 8) {
        lcd.print("Tomar café");
    } else if (hora >= 8 && hora < 9) {
        lcd.print("Ir à academia");
    } else if (hora >= 9 && hora < 12) {
        lcd.print("Programar");
    } else if (hora >= 12 && hora < 14) {
        lcd.print("Descanso");
    } else if (hora >= 14 && hora < 17) {
        lcd.print("Faculdade");
    } else if (hora >= 17 && hora < 23) {
        lcd.print("Livre");
    } else {
        lcd.print("Fora do horário");
    }

    delay(23);
}

//funcao que acessa um site e retorna a temperatura atual da minha cidade
void meteorologia(){

  String url = "https://www.climatempo.com.br/previsao-do-tempo/agora/cidade/384/aracaju-se";

  http.begin(url);

  int httpCode = http.GET();
  if (httpCode > 0) {
    String html = http.getString();
    int startPos = html.indexOf("<span class=\"-bold -gray-dark-2 -font-55 _margin-l-20 _center\">");
    int endPos = html.indexOf("</span>", startPos);

if (startPos != -1 && endPos != -1) {
    startPos += strlen("<span class=\"-bold -gray-dark-2 -font-55 _margin-l-20 _center\">") + 1;
    endPos = startPos + 2; 

    String frase = html.substring(startPos, endPos);

    lcd.setCursor(0, 0);
    lcd.print(frase);
    //simbolo de graus celsius 223
    lcd.write(223);

    lcd.print('C');
  
} else {
    lcd.setCursor(0,0);
    lcd.print("erro tag");
    lcd.clear();
    delay(23);
}
    
  }else{
    lcd.setCursor(0,0);
    lcd.print("erro em req");
    lcd.clear();
    delay(23);

  }
  http.end();
}

//funcao que criei para receber a ultima venda da hotmart, usando o sistemas de webhooks e um servidor intermediário na nuvem
void ultima_venda() {
  DataQuery_t data;
  lcd.setCursor(0,0);
  if(queryExecute(data,vendas,table))
  {
  String ultimavenda = data.getRowValue(0,0);
  lcd.print("ultima venda:");
  lcd.setCursor(0, 1);
  lcd.print(ultimavenda);
  Serial.println(ultimavenda);
  }else{
    lcd.print("nenhuma venda");
  }
  delay(2000);
}
//funcao para somar todos os meus lucros usando a webhook
void soma(){
  lcd.setCursor(0,0);
   DataQuery_t data;
  if(queryExecute(data,sum,table))
  {
  String soma = data.getRowValue(0,0);

  lcd.print(soma);
  Serial.println(soma);
  }else{
    lcd.print("nenhum dinheiro");

  }
  delay(2000);
}






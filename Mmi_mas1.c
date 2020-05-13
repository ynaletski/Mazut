//06.04.2020 YN -----\\//-----
#include "MD5.H"
#include "MD5C.C"

int dis_md5=0;
unsigned char str_1_md5[] = "Версия 01 Май.2020";
unsigned char str_2_md5[] = "MD5 идет расчет...";
unsigned char str_3_md5[] = "";
unsigned char str_4_md5[] = "";
unsigned char str_5_md5[] = "";
//06.04.2020 YN -----//\\-----

#include<7188xa.h>
#include<math.h>

#define Key_0        0x30
#define Key_1        0x31
#define Key_2        0x32
#define Key_3        0x33
#define Key_4        0x34
#define Key_5        0x35
#define Key_6        0x36
#define Key_7        0x37
#define Key_8        0x38
#define Key_9        0x39
#define Key_A        0x41
#define Key_B        0x42
#define Key_C        0x43
#define Key_D        0x44
#define Key_E        0x45
#define Key_F        0x46
#define Key_K        0x4b
#define Key_M        0x4d
#define Key_N        0x4e
#define Key_O        0x4f
#define Key_P        0x50
#define Key_T        0x54
#define Key_S        0x53

#define Key_blank    0x20
#define Key_dot      0x2e
#define Key_comma    0x2c
#define Key_termin    0xd
#define Key_modbus    0xa
#define Key_mask      0xf
#define Key_minus    0x2d
#define Key_dies     0x23
#define Key_cursor   0x5f
#define Key_usa      0x24
#define Key_adr      0x40
#define Key_true     0x21

#define Max_pnt         2   /*зЁб«® в®зҐЄ гзсв */
#define Len_name       16
#define Max_mmi_main   10
#define Max_mmi_point   7
#define Max_mmi_select  6
#define Max_mmi_exp     8
#define Len_select      4
#define Max_conf_all   99
#define Max_units_all  34
#define Max_sel_all   114
#define Max_number     40
#define Max_name_pnt    3
#define Max_dynam_all  69
#define Max_error         50  /*зЁб«® вЁЇ®ў ®иЁЎ®Є*/
struct cursor_mmi
{
  unsigned char enb; 
  unsigned char mode;
  unsigned char row,old;
  unsigned char size;
};
struct display_mmi
{
  unsigned char row,         /*бва®Є  ®в 0 ¤® 5*/
		point,       /*­®¬Ґа ўлЎа ­­®© в®зЄЁ*/
		flag,        /*ЇаЁ§­ Є ®Ў­®ў«Ґ­Ёп ўлў®¤  бЇЁбЄ  Ё¬с­*/
		num,         /*­®¬Ґа а иЁаҐ­Ёп ®в 0 ¤® 6*/
		evt,         /*б®ЎлвЁҐ(ўбҐЈ® ваЁ)*/
		write,       /*ЇаЁ§­ Є Ё§¬Ґ­Ґ­Ёп Є®­дЁЈга жЁЁ*/
		prm,         /*­®¬Ґа Ї а ¬Ґва  ў бЇЁбЄҐ ¤Ё­ ¬.Ї а ¬Ґва®ў*/
		old,
		page,        /*бва ­Ёж  ¤ЁбЇ«Ґп*/
	     suspend;        /*ЇаЁ®бв ­®ўЄ  ®Їа®б  Є« ўЁ в ¤«п ¬Ґ­о*/
  int pointer;
  unsigned char arch_num,size;
  unsigned char ret[5],ind_ret;
};
struct cursor_mmi             Cursor;
struct display_mmi            Display;

unsigned char *str_errors[]={
 " ","Массомер не отвечает"," "," ","Первый модуль не отвечает",
 "Второй модуль не отвечает"," "," "," ","Плотность нефти вне допуска",
 "Плотность воды вне допуска","Температура от массомера","Плотность от массомера"};
unsigned char *str_menu[]={
 "Общие настройки вычислителя",
 "Переменные процесса","Настройки процесса","Архив параметров суточный",
 "Архив параметров часовой","Настройки токовых модулей","Коррекция дата-время",
 "Установка нуля массомера","Расчет хеш-суммы MD5"}; //06.04.2020 add (,"Расчет хеш-суммы MD5")
unsigned char *str_menu1[]={
 "Первая точка учета",
 "Вторая точка учета","Третья точка учета","Четвертая точка учета"};
unsigned char *str_menu2[]={"Первый прибор","Второй прибор","Третий прибор","Четвертый прибор"};

const unsigned char psw[10] = {205,229,228,238,241,242,243,239,229,237};
/*­ бва®©ЄЁ Ї®ав */
const unsigned char set_pr[3] = {0,2,1};
const unsigned char set_st[2] = {1,2};
const unsigned char set_dt[2] = {8,7};
const unsigned long set_bd[8] = {1200,2400,4800,9600,19200,38400,57600,115200};
const char *conf_all[]={
" ",
"Статус точки","Выбор сужающего устройства","Выбор входа диффдавления",
"Выбор входа давления","Выбор входа температуры","Выбор входа вт. дифф",
"Статус алармов","Выбор теплоносителя","Межповерочный интервал",
"Единицы энергии","Диаметр трубопровода","Диаметр (ширина) СУ",
"Отсечка миним расхода","Верхний перекл диффман","Нижний перекл диффман",
"Начальный радиус кромки","Шероховатость трубопровода",
"КТР А трубопровода","КТР В трубопровода","КТР С трубопровода",
"КТР А сужающего устр","КТР В сужающего устр","КТР С сужающего устр",
"Нижний аларм расхода","Верхний аларм расхода","Нижний аларм диффдавл",
"Верхний аларм диффдавл","Гистерез алм диффдав","Нижний аларм давления",
"Верхний аларм давления","Гистерез алм давления","Нижний аларм температуры",
"Верхний аларм температ","Гистерез алм температ","Тег идентификатор",
"Адрес вычислителя","Контрактный час","Терминал оператора",
"Адрес датчика MVS #1","Адрес датчика MVS #2","Адрес датчика MVS #3",
"Адрес датчика MVS #4","Переход на зимнее/лет","Пароль оператора",
"Адрес модуля ICP #1","Адрес модуля ICP #2","Адрес модуля ICP #3",
"Адрес модуля ICP #4","Главный пароль","Телефонный номер",
"Настройка модема","Тип модуля ICP #1","Тип модуля ICP #2",
"Тип модуля ICP #3","Тип модуля ICP #4","Материал трубопровода",
"Материал суж устр","Конфигурация Modbus","Настройки порта COM",
"Архивная #","Способ термокоррекции","Конфигурация Hart",
"Коррекция мин расхода","Метод расчета","Единицы измерен AIN #",
"Нижняя граница AIN #","Верхняя граница AIN #","Параметр #",
"Плотность","Азот","Углекислый газ","Порт оператора","Data #",
"Обработка скрипта","Способ расчета кромки","Гистерез алм расхода",
"Единицы измерения AOT #","Нижняя граница AOT #",
"Верхняя граница AOT #","Панель","Нижний аларм брутто",
"Верхний аларм брутто","Гистерезис брутто","Нижний аларм влажн",
"Верхний аларм влажн","Гистерезис влажности","Адрес Массомер #1",
"Плотность нефти ст","Плотность воды ст","Год","Месяц","День","Час","Минута",
"Уровень компенсации","Период компенсации","Полярность выходов","Адрес Массомер #2"
};
 const unsigned char *dyn_all[]={
" ",
"Диффдавление","Давление абс","Температура","Плотность",
"Расход мас","Расход обм","Энтальпия","Масса ","Объём год ",
"Масса месяц","Энергия год ","Азот ","Угл газ",
"Объём месяц","Метан","Этан","Пропан","Энергия мес",
"н-Бутан","К сжимаемости","К расхода","К расширения",
"К неостроты","К шероховатости","К Рейнольдса","Число Рейнольдс",
"Вязкость динам","Скорость потока","Давление насыщ",
"Показат адиабат","Масса накоп","Объём накоп","и-Бутан",
"н-Пентан","и-Пентан","Гексан","Энергия","Энергия нак",
"Гептан","Октан","Нонан","Декан","Угар газ","Кислород",
"Водород","Сернист газ","Гелий","Расход","Плотность рабоч",
"Register #","Тоталайзер","Объём заправки","Влажность усредн",
"Брутто","Нетто ","Статус Массомера","Влажность","DRIVE GAIN",
"LIVE ZERO","Счетчик компенс","Плотность нефти","Плотность воды",
"Брутто нк","Нетто нк","Влажность нк","Вода","Масса тотал",
"Объем тотал"
};
/*[0]-­®¬Ґа Ї а ¬Ґва 
  [1]- ¤аҐб ЇҐаў®Ј® Ў ©в  Ї а ¬Ґва 
  [2]-ЇаЁ§­ Є Ї а®«п:1-Ї а®«м ­г¦Ґ­
  [3]-вЁЇ ¤ ­­ле:0-бва®Є ,1-Ў ©в,2-®¤Ё­.ўлЎ®а,3-¬­®¦.ўлЎ®а,
      4-ўҐйҐбвў.,5-¤«Ё­.жҐ«®Ґ*/
const char *name_mmi_exp[]={
 "  "," час"," сутки"," п сут"," месяц"," п мес", " год"," минут"};
const char *units_all[]={
 " "," мм"," кПа"," грС"," м3/ч"," т/ч",
 " ГДж"," Гкал"," кг/м3"," Па*с"," м/с"," Е-6/гС",
 " кДж/кг"," т"," м3"," ГДж/ч"," Гкл/ч"," стм3/ч",
 " ст.м3"," ккл/кг"," моль %"," обм %"," год"," т стм3",
 " кг/ч"," литр/ч"," кг"," литры"," бл руб"," мПа*с",
 " %"," B"," г/см3"," с"
};
const char *name_sel_all[]={
"Отключено","Включено","Диафрагма (Угловой)",
"Диафрагма (Фланцев)","Диафрагма (Трехрад)",
"Аннубар +10S","Аннубар +15/16S","Аннубар +25/26S",
"Аннубар +35/36S","Аннубар +45/46S","Аннубар 485_Size_1",
"Аннубар 485_Size_2","Аннубар 485_Size_3",
"Массовый расходомер","Константа","MVS #1","MVS #2","MVS #3",
"MVS #4","AIN #1","AIN #2","AIN #3","AIN #4","AIN #5",
"AIN #6","AIN #7","AIN #8","AIN #9","AIN #10","AIN #11",
"AIN #12","AIN #13","AIN #14","AIN #15","AIN #16",
"Модуль DIO первый","Модуль DIO второй","RTD #3","RTD #4",
"RTD #5","RTD #6","Вода","Пар","Стандарт (джоули)",
"Пользоват (калории)","Диффдавление","Давление",
"Температура","Расход мгновенный","Брутто ",
" ",
"Подключен к СОМ1","Подключен к СОМ2","Авто",
"Зимнее","Модуль AIN первый","Модуль AIN второй",
"Модуль AOUT первый","Модуль AOUT второй","Материал",
"Коэффициент","Сталь 8","Сталь 10","Сталь 15",
"Ст 15М/20М","Сталь 16М","Сталь 20","Сталь 25",
"Сталь 30/35","Х6СМ/Х7СМ","12МХ","12Х18Н9/10Т",
"316 (S31600/CF8M)","14X17H2","15ХМА","15X1М10",
"15Х5М","17Х18Н9","20Х23Н13","36Х18Н25С2","301 (S30100)",
"12X1МФ","15Х1М1Ф","15Х12ЕНМФ","NX-19 mod","GERG-91 mod",
"ВНИЦ-СМВ","Фиксированная","Изменяемая","I-7060","I-7080",
"I-7040","Дозированное","До заполнения","От компьютера",
"Автономное","За период поверки","За время эксплуатац",
"Сталь 40/45","Сталь 20Л","Сталь 25Л","Сталь 35Л",
"Сталь 45Л","12Х18Н10Т/12Т","12Х18Н9ТЛ","25Х1МФ",
"18Х2Н4МА","12Х19Н9Т","10Х14Г14Н4Т","31Х19Н9МВБТ",
"37Х12Н8Г8МФБ","Влажность","Отрицательная","Положительная"
};
const unsigned char name_mmi_select[Max_mmi_select][Len_select]={
 {0x22,0x31,0x22,0x20},{0x22,0x32,0x22,0x20},{0x22,0x33,0x22,0x20},
 {0x22,0x34,0x22,0x20},{0x22,0x35,0x22,0x20},{0x22,0x36,0x22,0x20},};
const unsigned char name_arch[Max_name_pnt][6]={{205,229,238,239,240,0x20},/*ЌҐ®Їа*/
 {193,224,231,238,226,Key_dies},/*Ѓ §®ў*/{197,238,239,239,235,237}/*„®Ї®«­*/};
unsigned char mmi_str[30],Size_str;/* ЎгдҐа Є« ўЁ вгал Ё ¤ЁбЇ«Ґп ваҐвЁ© Ї®ав */
unsigned char Vertical,Horizont,/*Ї®§ЁжЁп бЁ¬ў®«  8*30 */
	      mmi_pass,/*­®¬Ґа Їа®е®¤  ЇаЁ ®в®Ўа ¦Ґ­ЁЁ бва®ЄЁ*/
	      enter_ind,/*ў Є®­дЁЈ:зЁб«® ўў®¤ бЁ¬ў®«®ў*/
	      mmi_num_sel,/*зЁб«® ўлЎ®а®ў ¤«п Ї а ¬Ґва */
	      mmi_size,mmi_arc_page,flg_init;
unsigned char mmi_val[6],coord[8],count_smb,flg_zero_meter,
	      evt_meter[Max_pnt],nmb_meter, flg_dyn_clr;
int mmi_arc;/*гЄ § вҐ«м  аеЁў */
unsigned mmi_seg,mmi_adr;/*бҐЈ¬Ґ­в Ё  ¤аҐб*/
extern unsigned char size_max;
unsigned char mmi_sel[30],err[Max_error];

/********* гбв ­®ўЄ  бва ­Ёжл ¤ЁбЇ«Ґп ****************************/
void SetDisplayPage (unsigned char page)
{ Display.evt=1; Display.page=page;}
/*************************/
void SaveOldPageMMI (void)
{
  Display.ret[Display.ind_ret]=Display.page; Display.ind_ret++;
}
/*************************/
void GoToMenuMMI (unsigned char num_page)
{
  Cursor.enb=1; Cursor.row=0; Cursor.mode=1; Display.flag=1;
  Display.row=0; Cursor.size=0; SaveOldPageMMI(); Display.num=0;
  Display.suspend=1;SetDisplayPage(num_page);
}
/******* д®а¬Ёа®ў ­ЁҐ § Їа®б  ў MMI(Ё­вҐадҐ©б зҐ«®ўҐЄ-¬ иЁ­ )****/
unsigned char SendToMMI (unsigned char typ_port)
{
  unsigned char count,i,typ_pool;unsigned char buf_mmi[40],cr[2];
  buf_mmi[0]=Key_usa;buf_mmi[1]=Key_0;buf_mmi[2]=Key_0;
  switch (Display.evt)
  {
    case 0:buf_mmi[3]=Key_K;count=4;typ_pool=15;break;/*®Їа®б Є« ўЁ вгал*/
    case 1:buf_mmi[3]=Key_P;buf_mmi[4]=hex_to_ascii[(Display.page >> 4) & Key_mask];
	   buf_mmi[5]=hex_to_ascii[Display.page & Key_mask];count=6;
	   typ_pool=16;Display.evt=0;break;/*гбв ­®ўЄ  бва ­Ёжл ¤ЁбЇ«Ґп*/
    case 2:buf_mmi[3]=Key_T;buf_mmi[4]=hex_to_ascii[Vertical];
	   buf_mmi[5]=hex_to_ascii[(Horizont >> 4) & Key_mask];
	   buf_mmi[6]=hex_to_ascii[Horizont & Key_mask];
	   for (i=0;i< count_smb;i++) buf_mmi[7+i]=mmi_str[i];
	   count=7+count_smb;typ_pool=17;if (Display.suspend==0) Display.evt=0;break;/*ЇҐаҐ¤ з  бва®ЄЁ*/
    case 3:buf_mmi[3]=Key_S;count=4;typ_pool=18;Display.evt=0;break;/*®Їа®б бва ­Ёжл*/
    default:count=0;typ_pool=0;Display.evt=0;break;
  } if (count > 0)
  {
    CalcCheckSum(buf_mmi,count,cr);buf_mmi[count]=hex_to_ascii[cr[0]];
    buf_mmi[count+1]=hex_to_ascii[cr[1]];buf_mmi[count+2]=Key_termin;
    count=count+3;for (i=count;i>0;i--) buf_mmi[i]=buf_mmi[i-1];
    buf_mmi[0]=Key_termin;count++;
    if (typ_port==1) ToComBufn_1(buf_mmi,count);else
    if (typ_port==2) ToComBufn_2(buf_mmi,count);else
    if (typ_port==3) ToComBufn_3(buf_mmi,count);
  } return typ_pool;
}
/********* Їа®ўҐаЄ  ­ ¦ в®© Є« ўЁиЁ  *******************************/
unsigned char KeyFound (unsigned char buf_mmi[],unsigned char code_key1,
			unsigned char code_key2,unsigned char count)
{ /*ЁбЇ®«м§гҐвбп ¤«п Ї®ЁбЄ  Ї ал Є®¤®ў ­ ¦ в®© Є« ўЁиЁ*/
  unsigned char i,j;j=0;
  for (i=4;i < count-1;)
  {
    if ((buf_mmi[i]==code_key1)&&(buf_mmi[i+1]==code_key2)) {j=1;break;}
    i=i+2;
  } if (j==0) return 0;else return 1;
}
/*********** ®зЁбвЄ  ЎгдҐа  ўлў®¤  ­  нЄа ­ *********************/
void ClearBuffer (void)
{
  unsigned char i;for (i=0;i< 30;i++) mmi_str[i]=Key_blank;
}
/************ ЇаҐ®Ўа §®ў ЁҐ ў бЁ¬ў®«м­го бва®Єг ******************/
void FloatToString (float val,unsigned char buf_str[],
		   unsigned char offset)
{ /*ЁбЇ®«м§гҐвбп ЇаЁ ўлў®¤Ґ Є®­дЁЈ.Ё«Ё  аеЁў­®Ј® §­ зҐ­Ё©*/
 /* unsigned char i,buf[50],flag,j;flag=j=0;
  gcvt(val,10,buf);
  for (i=0;i<10;i++) if (buf[i] !=0)
  {
    buf_str[i+offset]=buf[i];
    if (flag==1) j++;if ((val>=1 && j>=3)||(val<1 && j>=6)) break;
    if (buf[i]==Key_dot) flag=1;
  } else break; */
  unsigned char i,buf[50],flag; double musor,value;
  flag=0; if (val < 0) flag=1; value=fabs(val);
  if (value<100000)
  {
    value=value*100; musor=modf(value, &value);
    if (musor >= 0.5) value=value+1; value=value/100;
  } else
  {
    modf(value, &value);
    if (value>=10000000)
    {
      value=value/100000; musor=modf(value, &value);
      if (musor >= 0.5) value=value+1;
      value=value*100000;
    }
  }
  if (flag == 1) value=-value; gcvt(value,8,buf);
  for (i=0;i<10;i++) if (buf[i] !=0) buf_str[i+offset]=buf[i]; else break;
}
/*********** ЇаҐ®Ўа §®ў ­ЁҐ Ў ©в  ў ¤ў  бЁ¬ў®«  ***********/
void ByteToString (unsigned char val,unsigned char index,unsigned char typ)
{ /*ЁбЇ®«м§гҐвбп ЇаЁ ўлў®¤Ґ  аеЁў­ле ¤ вл Ё ўаҐ¬Ґ­Ё*/
  unsigned char a,d,e,c,b;c=10;b=val;a=0;
  while (c>=1)
  {
    d=b/c; 
    if (typ==1 && a==0 && d==0) 
    {mmi_str[index]=0x20;index++;goto M;}
    if (d < 10)
    { mmi_str[index]=hex_to_ascii[d & Key_mask];index++;} else
    {
      e=d/10; mmi_str[index]=hex_to_ascii[e & Key_mask];index++;
      e=d-e*10; mmi_str[index]=hex_to_ascii[e & Key_mask];index++;
    } 
M:  b=b-d*c;c=c/10;a++;
  }
}
/************** ЇаҐ®Ўа §®ў ­ЁҐ жҐ«®Ј® ў бв®аЄг ******************/
unsigned char IntegerToString (unsigned long val)
{
  unsigned long d;unsigned char buf[10],i,j;i=0;
  while (val > 0)
  {
    d=val/10;buf[i]=hex_to_ascii[(val-d*10) & Key_mask];
    i++;val=d;
  } for (j=0;j<i;j++) mmi_str[j]=buf[i-j-1];return i;
}
/*********** ®в®Ўа ¦Ґ­ЁҐ ўўҐ¤с­­®Ј® §­ Є  *******************/
void EnterKey (unsigned char code_symbol,unsigned char *index)
{ /*ЁбЇ®«м§гҐвбп ЇаЁ ўў®¤Ґ Ї а®«п Ё«Ё Є®­дЁЈ.§­ зҐ­Ёп*/
   if (*index < 8)
   {
     mmi_str[*index]=code_symbol;count_smb=8;
     mmi_str[*index+1]=Key_cursor;*index=*index+1;Display.evt=2;
   }
}
/*********** г¤ «Ґ­ЁҐ ўўҐ¤с­­®Ј® §­ Є  ***********************/
void DeleteKey (unsigned char *index)
{ /*ЁбЇ®«м§гҐвбп ЇаЁ ўў®¤Ґ Ї а®«п Ё«Ё Є®­дЁЈ.§­ зҐ­Ёп*/
   if (index > 0)
   {
     mmi_str[*index]=Key_blank;*index=*index-1;
     mmi_str[*index]=Key_cursor;count_smb=8;Display.evt=2;
   }
}
/** ўў®¤ жЁда®ў®Ј® §­ зҐ­Ёп ¤«п:Ї а®«п,Ё§¬Ґ­.Є®­дЁЈ, аеЁў®ў **/
unsigned char EnterFigure (unsigned char buf_mmi[],unsigned char count)
{ /*Є®¤л Є« ўЁи ®в "0" ¤® "9",ЇҐаҐў®¤ ў бЁ¬ў®« Ё жЁдаг*/
  const unsigned char dec_key[10]={Key_3,Key_C,Key_D,Key_F,Key_E,
				   Key_8,Key_9,Key_B,Key_A,Key_1};
  unsigned char i,flag;/*num_key=16;*/flag=0;
  if (enter_ind < 9) for (i=0;i<10;i++)
  {
    if (KeyFound (buf_mmi,Key_0,dec_key[i],count)==1)
    { EnterKey(Key_0+i,&enter_ind);flag=1;break; }
  } return flag;
}
/********* ў®§ўа в ўўҐ¤с­­®© жЁдал  ******************************/
unsigned char ConvertToDec (unsigned char symbol)
{/*Є®¤"10"¬Ё­гб,Є®¤"11"§ Їпв п,ЇҐаҐў®¤ ¤ҐбпвЁз­®Ј® бЁ¬ў®«  ў жЁдаг*/
  unsigned char dec;
  if ((symbol>47)&&(symbol<58)) dec=symbol-48;
  if (symbol==Key_minus) dec=10;if (symbol==Key_dot) dec=11;
  return dec;
}
/******* Ї®Є §лў Ґв Ї®§ЁжЁо ¤«п ўў®¤  бЁ¬ў®«  ******************/
void ViewCursor (unsigned char index)
{
   if (index==0)
   { mmi_str[0]=Key_cursor;count_smb=8;Display.evt=2;}
}
/********* Ї®«гзҐ­ЁҐ ­®ўле ­ бва®ҐЄ  аеЁў  ЇаЁ звҐ­ЁЁ *************/
void GetArcReadPoint(int *pointer,unsigned *segment,unsigned char *page)
{
  switch (*page)
  {
    case 0:*page=2;*segment=0xc000;
	   *pointer=ReadNVRAM(17)*256+ReadNVRAM(18);break;
    case 1:*page=0;*segment=0xd000;
	   *pointer=ReadNVRAM(13)*256+ReadNVRAM(14);break;
    case 2:*page=1;*segment=0xe000;
	   *pointer=ReadNVRAM(15)*256+ReadNVRAM(16);break;
  }
}
/**********************************/
void MoveCursorMMI (unsigned char buf_mmi[],unsigned char broad,
                                             unsigned char count)
{
  M1:if (Cursor.enb==1)
    {
      if (Cursor.mode==1) 
      {
	Horizont=0; Vertical=Cursor.row+1; count_smb=1; ClearBuffer();
        Cursor.enb=0; mmi_str[0]=0x3e; Display.evt=2; goto M2;
      } else
      {
	Vertical=Cursor.old+1; count_smb=1; ClearBuffer(); Display.evt=2;
        Cursor.mode=1; Horizont=0; goto M2;
      }
    } else if (KeyFound(buf_mmi,Key_0,Key_3,count)==1 && Cursor.row<(broad-1))
    {
      Cursor.old=Cursor.row; Cursor.row=Cursor.row+1; Cursor.enb=1;
      Cursor.mode=0; goto M1;
    } else if (KeyFound(buf_mmi,Key_0,Key_F,count)==1 && Cursor.row>0)
    {
      Cursor.old=Cursor.row; Cursor.row=Cursor.row-1; Cursor.enb=1;
      Cursor.mode=0; goto M1;
    }
  M2:
}
/******************************/
void ReturnToMenuMMI (void)
{
  unsigned char num_page;
  Cursor.enb=1; Cursor.row=0; Cursor.mode=1; Display.flag=1;
  Display.row=0; Cursor.size=0; Display.suspend=1; 
  if (Display.ind_ret>0) 
  {
    num_page=Display.ret[Display.ind_ret-1]; Display.ind_ret--;
  } else num_page=10; SetDisplayPage(num_page);
}
/*********** Ё§¬Ґ­Ґ­ЁҐ Є®­дЁЈга жЁЁ Ё § ЇЁбм б®ЎлвЁп ***************/
unsigned char ConfigParamChange (unsigned char value[],unsigned char size,
				 unsigned char addr)
{
  unsigned char buf_evt[16],j,flag;flag=0;FormateEvent(buf_evt);
  for (j=0;j< size;j++)
  {
    if (value[j] != mmi_val[j])
    {
      EnableEEP();WriteEEP(Display.point,addr+j,value[j]);ProtectEEP();
      flag=1;
    } buf_evt[6+j]=mmi_val[j];buf_evt[10+j]=value[j];
  }
  if (flag == 1) /*§ ЇЁбм б®ЎлвЁп ®в вҐа¬Ё­ « */
  {
    buf_evt[15]=Display.point+1+128;buf_evt[14]=Display.prm;WriteEvent(buf_evt,0);
    return Display.point+1;
  } else return 0;
}
/******************************/
unsigned char  MoveListMMI (unsigned char buf_mmi[],unsigned char count,
                  unsigned char size_max)
{
  unsigned char flag;
  if (KeyFound(buf_mmi,Key_0,Key_5,count)==1 && Display.num>=6)
  {
    Display.num=Display.num-6;Horizont=0;Display.row=0;Display.flag=1;flag=1;
    Cursor.size=0;Display.suspend=1;
  } else
  if (KeyFound(buf_mmi,Key_0,Key_7,count)==1 && Display.num<(size_max-6))
  {
    Display.num=Display.num+6;Horizont=0;Display.row=0;Display.flag=1;flag=1;
    Cursor.size=0;Display.suspend=1;
  } else flag=0; return flag;
}
/******************************/
void WriteMenuToMMI (unsigned char menu[], unsigned char size_menu)
{
  unsigned char i,j,flag;
  ClearBuffer(); Vertical=Display.row+1;
  if ((Display.num+Display.row)<size_menu)
  {
    j=strlen(menu); for (i=0;i<j;i++) mmi_str[i]=menu[i];
    Cursor.size++;
  } count_smb=28;Horizont=2;Display.evt=2;Display.row++;
  if (Display.row > 5)
  {
    Display.row=0; Display.flag=0; Cursor.mode=0; Cursor.old=Cursor.row;
    Cursor.row=0; Cursor.enb=1;Display.suspend=0;
  }
}
/******* ®Ўа Ў®вЄ  ®вўҐв  ®в MMI(вҐа¬Ё­ « ®ЇҐа в®а ) *****/
void ReadFromMMI (unsigned char buf_mmi[],unsigned char count,
		  double dyn_prm)
{
  /*[]-[]-[]-*/
  unsigned char i,j,k,cr[4],buf_evt[16],flg;float value;int pnt_evt;
  unsigned long st_meter;
  switch (Display.page)
  {
    case 0: case 1: case 2: case 3: case 4: case 5:
    case 6: case 7: case 8: /*case 9:*/ /*заголовок*/ // //06.04.2020 YN rem case 9:
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) /*"D"*/
      GoToMenuMMI(10); else
      { /* ўЁ§г «Ё§ жЁп Є®­ва®«м­®© бг¬¬л */
	ClearBuffer(); Display.suspend=0; k=0;
        for (i=0;i<3;i++) /*ўлў®¤Ёв ¤ вг*/
        { 
          ByteToString(ReadNVRAM(2-i),k,0);if (i != 2) mmi_str[k+2]=Key_dot;k=k+3;
	} k=9;count_smb=18;
	for (i=0;i<3;i++) /*ўлў®¤Ёв ўаҐ¬п*/
	{ 
          ByteToString(ReadNVRAM(3+i),k,0);if (i != 2) mmi_str[k+2]=0x3a;k=k+3;
	} Horizont=5;Vertical=4;Display.evt=2;
      } break;
//06.04.2020 YN -----\\//-----
	case 9:
      	if (KeyFound(buf_mmi,Key_0,Key_6,count)==1) /*отказ от изменения*/
      	{
			flg_zero_meter=0;flg_dyn_clr=0;Cursor.enb=1; Cursor.row=0;
			Cursor.mode=1; Display.flag=1;Display.row=0; Cursor.size=0;
			Display.suspend=1;SetDisplayPage(10); dis_md5=0;
      	}
		else if(dis_md5 == 0)
		{	
			strcpy(mmi_str,str_1_md5);
			//printCom(4,"\n\r %s", buf_mmi);
			Vertical=2;Horizont=3;count_smb=24;Display.evt=2;
			dis_md5 = 1;
		}
		else if(dis_md5 == 1)
		{
			strcpy(mmi_str,str_2_md5);
			Vertical=3;Horizont=1;count_smb=14;Display.evt=2;
			dis_md5 = 2;
		}
		else if(dis_md5 == 2)
		{
			if(fl_md_fst==0) f_md5(1);
			else {dis_md5 = 3; sprintf(str_3_md5,"MD5 (%s,%ld)=", filename,lgth_fl);}
		}
		else if(dis_md5 == 3)
		{
			memset(mmi_str, 0, sizeof(mmi_str));
			strcpy(mmi_str,str_3_md5);
			Vertical=3;Horizont=1;count_smb=(strlen(str_3_md5)+1);Display.evt=2;
			dis_md5 = 4;
			sprintf(str_4_md5,"%02x%02x%02x%02x%02x%02x%02x%02x", digest[0],digest[1],digest[2],digest[3],digest[4],digest[5],digest[6],digest[7]);
		}
		else if(dis_md5 == 4)
		{
			memset(mmi_str, 0, sizeof(mmi_str));
			strcpy(mmi_str,str_4_md5);
			Vertical=4;Horizont=6;count_smb=(strlen(str_4_md5)+1);Display.evt=2;
			dis_md5 = 5;
			sprintf(str_5_md5,"%02x%02x%02x%02x%02x%02x%02x%02x", digest[8],digest[9],digest[10],digest[11],digest[12],digest[13],digest[14],digest[15]);
		}
		else if(dis_md5 == 5)
		{
			memset(mmi_str, 0, sizeof(mmi_str));
			strcpy(mmi_str,str_5_md5);
			Vertical=5;Horizont=6;count_smb=(strlen(str_5_md5)+1);Display.evt=2;
			dis_md5 = 6;
		}
		else {}
	break;
	//06.04.2020 YN -----//\\-----	  
    case 10:/*®б­®ў­®Ґ ¬Ґ­о*/
       if (Display.flag==1)
   WriteMenuToMMI(str_menu[Display.num+Display.row],9); else   //06.04.2020 YN was 8 now 9
       MoveCursorMMI(buf_mmi,Cursor.size,count);
       MoveListMMI (buf_mmi,count,10);
       if (KeyFound(buf_mmi,Key_0,Key_6,count)==1) 
       { Display.flag=0;ReturnToMenuMMI();} else
       if (KeyFound(buf_mmi,Key_0,Key_2,count)==1) 
       switch (Cursor.row+Display.num)
       { 
	case 0: Display.point=7; Display.write=0; GoToMenuMMI(20);break;
	case 1: GoToMenuMMI(11); break;
	case 2: GoToMenuMMI(12); break;
	case 3: Display.point=1; GoToMenuMMI(13); break;
	case 4: Display.point=0; GoToMenuMMI(13); break;
        case 5: Display.point=6; Display.write=0; GoToMenuMMI(20);break;
	case 6: Display.point=60; Display.write=0; GoToMenuMMI(20);break;
	case 7: GoToMenuMMI(27); break;
	case 8: enter_ind=0; SetDisplayPage(9); break; //06.04.2020 YN add
	/*flg_zero_meter=1;ClearBuffer();Horizont=10;Vertical=3;
		SetDisplayPage(17); break;*/
       }
	break;
    case 11:/*¬Ґ­о ўлЎ®а  в®зЄЁ ¤«п Їа®б¬®ва */
      if (Display.flag==1) WriteMenuToMMI(str_menu1[Display.num+Display.row],Max_pnt); else
      MoveCursorMMI(buf_mmi,Cursor.size,count);
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) ReturnToMenuMMI(); else
      if (KeyFound (buf_mmi,Key_0,Key_2,count)==1)
      {
	Display.point=Cursor.row; Horizont=0; Display.row=0; Display.num=0; Display.flag=1;
	mmi_pass=0; Display.suspend=1;SaveOldPageMMI(); SetDisplayPage(14);
      } break;
    case 12:/*¬Ґ­о ўлЎ®а  в®зЄЁ ¤«п Є®­дЁЈга жЁЁ*/
      if (Display.flag==1) WriteMenuToMMI(str_menu1[Display.num+Display.row],Max_pnt); else
      MoveCursorMMI(buf_mmi,Cursor.size,count);
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) ReturnToMenuMMI(); else
      if (KeyFound (buf_mmi,Key_0,Key_2,count)==1)
      { Display.point=Cursor.row; Display.write=0; GoToMenuMMI(20);} break;
    case 24:/*Їа®б¬®ва ®иЁЎ®Є*/
	if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
	{Display.num=0;ReturnToMenuMMI();} else
	if (Display.flag == 1)
	{
	  ClearBuffer();Vertical=Display.row+1;
	  if ((Display.num+Display.row)<13)
	  {
            for (i=mmi_pass;i<13;i++) if (err[i]>=10)
            {
	      j=strlen(str_errors[i]);
	      for (k=0;k<j;k++) mmi_str[k]=str_errors[i][k];mmi_pass=i+1;break; 
            }
	    count_smb=28;Horizont=0;Display.row++;
	    if (Display.row > 5) {Display.row=Display.flag=0;Display.suspend=0;}
	    Display.evt=2;
	  }
	} break;
    case 14:/*Їа®б¬®ва ¤® 6 Ї а ¬Ґва®ў*/
	if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
	{Display.num=0;ReturnToMenuMMI();}else/*"D"ЇҐаҐе®¤ ў ¬Ґ­о ўлЎ®а  в®зЄЁ ¤«п Їа®б¬®ва */
	if (MoveListMMI (buf_mmi,count,size_max)==1) mmi_pass=0;else
        {
	  ClearBuffer();Vertical=Display.row+1;
	  if (mmi_pass==0) /*б¬Ґ­  бЇЁбЄ */
	  {  /*ўлў®¤ Ё¬Ґ­Ё Ї а ¬Ґва  §  ®¤Ё­ Їа®е®¤*/
	    if ((Display.num+Display.row)<size_max && coord[0]<Max_dynam_all)
	    {
	      j=strlen(dyn_all[coord[0]]);
	      for (i=0;i<j;i++) mmi_str[i]=dyn_all[coord[0]][i];
	      if ((coord[2]==2 || coord[2]==3) && coord[1]<Max_mmi_exp && coord[1]>0)
	      {
	        k=strlen(name_mmi_exp[coord[1]]);
		for (i=j;i<j+k;i++)
		mmi_str[i]=name_mmi_exp[coord[1]][i-j];
		mmi_size=j+k;
	      } else mmi_size=j; j=strlen(units_all[coord[3]]);
	      for (i=mmi_size;i<mmi_size+j;i++)
	      if (coord[3] < Max_units_all)
	      mmi_str[i]=units_all[coord[3]][i-mmi_size];
              if (coord[4]==1) ByteToString(coord[5],mmi_size,1);
	    } count_smb=22;Horizont=0;mmi_pass=1;Display.evt=2;
	  } else
	  { /*ўлў®¤ §­ зҐ­Ёп Ї а ¬Ґва */
	      if((Display.num+Display.row)<size_max) FloatToString(dyn_prm,mmi_str,0);
	      count_smb=8;Horizont=22;Display.row++;
	      if (Display.row > 5) {Display.row=Display.flag=0;Display.suspend=0;}
              if (Display.flag==1) mmi_pass=0;Display.evt=2;
	  }   	     
	} break;
    case 15:/*ўў®¤ §­ зҐ­Ёп*/
	if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) /*®в¬Ґ­  Ё§¬Ґ­ Є®­дЁЈ*/
	{
	  mmi_pass=Display.write=enter_ind=0;Horizont=0;Display.flag=1;
	  Vertical=2;SetDisplayPage(16);
	} else
	if (KeyFound (buf_mmi,Key_1,Key_E,count)==1) DeleteKey(&enter_ind);else
	if (EnterFigure(buf_mmi,count) != 1)
	{
	  if (KeyFound (buf_mmi,Key_1,Key_B,count)==1) /*§ Їпв п*/
	      EnterKey(Key_dot,&enter_ind);else
	  if (KeyFound (buf_mmi,Key_0,Key_2,count)==1 && enter_ind>0)
	  { /*ўў®¤ ­®ў®Ј® Є®­дЁЈга жЁ®­­®Ј® §­ зҐ­Ёп*/
	    value=atof(mmi_str);
	    if (coord[3] == 1 || coord[3] == 2)
	    { /*¤«п Ў ©в®ўле §­ зҐ­Ё© а §¤Ґ«ЁвҐ«м ®вбгвбвўгҐв*/
	      cr[0]=value;flg_init=ConfigParamChange(cr,1,coord[2]);
	    }
	    if (coord[3] == 4)
	    { /*¤«п ¤Ґ©бвўЁвҐ«м­ле §­ зҐ­Ё©*/
	      ConvToBynare(value,cr);
	      flg_init=ConfigParamChange(cr,4,coord[2]);
	    } if (coord[3] == 60 && coord[2]<5)
	    {
	      cr[0]=value; WriteNVRAM(coord[2],cr[0]);
	      if (coord[2] >= 3)
		SetTime(ReadNVRAM(3),ReadNVRAM(4),ReadNVRAM(5));
	      if (coord[2] < 3)
		SetDate(ReadNVRAM(0)+2000,ReadNVRAM(1),ReadNVRAM(2));
	    } mmi_pass=Display.write=enter_ind=0;Horizont=0;Display.flag=1;
	      Vertical=2;SetDisplayPage(16);/*ўЁ§г «Ё§ жЁп Ё§¬Ґ­Ґ­Ёп*/
	  } else ViewCursor(enter_ind);
	} break;
    case 16:/*Ё§¬Ґ­Ґ­ЁҐ Є®­дЁЈга жЁЁ*/
	if (Display.flag==1)
	{ ClearBuffer();
	  if (mmi_pass==0)
	  {
	    j=strlen(conf_all[coord[0]]);
	    for (i=0;i<j;i++)
	    mmi_str[i]=conf_all[coord[0]][i];k=strlen(units_all[coord[5]]);
	    if (coord[5]>0)
	    for (i=j;i<j+k;i++)
	    mmi_str[i]=units_all[coord[5]][i-j];else
	    if (coord[4]<=40) ByteToString(coord[4]+1,j,1);
	    count_smb=28;mmi_pass=1;
	  } else
	  {
	    if (coord[3]==4)
	    {
	      if (SecurityConvert(ReadEEP(Display.point,coord[2]),
		ReadEEP(Display.point,coord[2]+1),ReadEEP(Display.point,coord[2]+2),
		ReadEEP(Display.point,coord[2]+3),mmi_val)==0)
	      value=ConvToFloat(mmi_val[0],mmi_val[1],mmi_val[2],mmi_val[3]);
	      FloatToString(value,mmi_str,0);
	    } else if (coord[3]==1 || coord[3]==3)
	    {
	      mmi_val[0]=ReadEEP(Display.point,coord[2]);
	      ByteToString(mmi_val[0],0,1);
	    } else if (coord[3]==2)
	    {
	      mmi_val[0]=ReadEEP(Display.point,coord[2]);
	      j=strlen(name_sel_all[mmi_sel[mmi_val[0]]]);
	      if (mmi_val[0]<30 && mmi_sel[mmi_val[0]]<Max_sel_all)
	      for (i=0;i<j;i++)
	      mmi_str[i]=name_sel_all[mmi_sel[mmi_val[0]]][i];
	    } else if (coord[3]==6)
	    {
	      mmi_val[0]=ReadEEP(Display.point,coord[2]);
	      i=IntegerToString(set_bd[mmi_val[0] & 15]);
	      mmi_str[i]=mmi_str[i+2]=Key_comma;
	      mmi_str[i+1]=hex_to_ascii[set_dt[(mmi_val[0] &16)>>4] & Key_mask];
	      switch ((mmi_val[0] &192)>>6)
	      {
		case 0:mmi_str[i+3]=Key_N;break;case 1:mmi_str[i+3]=Key_O;break;
		case 2:mmi_str[i+3]=Key_E;break;
	      }
	    } else if (coord[3]==0 || coord[3]==10)
	    {
	      for (i=0;i<8;i++) mmi_str[i]=ReadEEP(Display.point,coord[2]+i);
	    } else if (coord[3]==5 || coord[3]==9)
	    {
	      for (i=0;i<10;i++) mmi_str[i]=psw[i];
	    } else if (coord[3] == 8)
	    {
	      mmi_val[0]=ReadEEP(Display.point,coord[2]);
	      if (mmi_val[0] < Max_name_pnt) for (i=0;i<6;i++)
	      mmi_str[i]=name_arch[mmi_val[0]][i];
	      if (mmi_val[0] != 0)
	      {
		if (mmi_val[0] == 1)
		{
		  mmi_val[1]=ReadEEP(Display.point,coord[2]+1)+1;
		  mmi_str[6]=hex_to_ascii[mmi_val[1] & Key_mask];
		}
		mmi_str[7]=Key_comma;
		j=strlen(dyn_all[coord[7]]);
		if (coord[7]> 0 && coord[7]<Max_dynam_all)
		for (i=0;i<j;i++)
		mmi_str[8+i]=dyn_all[coord[7]][i];
		mmi_val[3]=ReadEEP(Display.point,coord[2]+3);
		if (mmi_val[3]>3 && mmi_val[3]<Max_mmi_exp)
		for (i=0;i<6;i++)
		mmi_str[8+j+i]=name_mmi_exp[mmi_val[3]][i];
	      }
	    } if (coord[3] == 12)
            {
	      mmi_val[0]=ReadEEP(Display.point,coord[2]);
	      k=strlen(units_all[mmi_val[0]]);
	      if (mmi_val[0]<Max_units_all) for (i=0;i<k;i++)
	      mmi_str[i]=units_all[mmi_val[0]][i];
	    } if (coord[3] == 60)
	    {
	      mmi_val[0]=ReadNVRAM(coord[2]);ByteToString(mmi_val[0],0,1);
	    } Horizont=2;Vertical=4;count_smb=29;Display.flag=0;
	  }   Display.evt=2;
	} else
	if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) /*"ESC"ЇҐаҐе®¤ ў ¬Ґ­о*/
	{ Display.num=Display.old; ReturnToMenuMMI();} else
	if (KeyFound (buf_mmi,Key_0,Key_4,count)==1)
	{
	  if (coord[6] !=2) /*"F1"ўў®¤ Ї а®«п ¤«п Ё§¬Ґ­Ґ­Ёп*/
	  {
	    ClearBuffer();Horizont=10;Vertical=3;
	    if (coord[6]==1) SetDisplayPage(17);else
	    {Display.write=1;enter_ind=0;SetDisplayPage(15);}
	  } else  SetDisplayPage(22);
	} 
	break;
    case 17:/*ўў®¤ Ї а®«п*/
       if (KeyFound(buf_mmi,Key_0,Key_6,count)==1) /*®вЄ § ®в Ё§¬Ґ­Ґ­Ёп*/
       {
	 if (flg_zero_meter==0 && flg_dyn_clr==0)
	 {
	   mmi_pass=0;Horizont=0;Display.flag=1;Display.write=0;enter_ind=0;
	   Vertical=2;SetDisplayPage(16);
	 } else
	 {
	   flg_zero_meter=0;flg_dyn_clr=0;Cursor.enb=1; Cursor.row=0;
	   Cursor.mode=1; Display.flag=1;Display.row=0; Cursor.size=0;
	   Display.suspend=1;SetDisplayPage(10);
	 }
       } else
       {
	 if (KeyFound(buf_mmi,Key_1,Key_E,count)==1) DeleteKey(&enter_ind);else/*г¤ «Ґ­ЁҐ Ї®б«Ґ¤­ҐЈ®*/
	 if (EnterFigure(buf_mmi,count)!=1);/*ўў®¤ §­ зҐ­Ё© ®в "0"¤®"9"*/
	 {
	   if (KeyFound(buf_mmi,Key_0,Key_2,count)==1 && enter_ind>0)
	   { /*ўў®¤ Ї а®«п ­  Ё§¬Ґ­Ґ­ЁҐ Є®­дЁЈга жЁЁ*/
	     /*value=ConvertToNumber(enter_ind); /*ўлзЁб«Ґ­ЁҐ нв «®­­®Ј® Ї а®«п*/
	     value=atof(mmi_str);
	     if (value != dyn_prm) SetDisplayPage(18);else
	     { /*Ї а®«м ўўҐ¤с­ Їа ўЁ«м­®*/
	       if (flg_zero_meter==0 && flg_dyn_clr==0)
	       {
		 ClearBuffer();if (coord[3]==2)
		 {
		   Horizont=Display.row=Display.num=0;Display.flag=1;
		   SetDisplayPage(21);
		 } else
		 {
		   SetDisplayPage(15);Display.write=1;enter_ind=0;
		   Horizont=10;
		 }
	       } else if (flg_zero_meter==1) {enter_ind=0;SetDisplayPage(26);}
	       else if (flg_dyn_clr==1)
	       {
		 flg_dyn_clr=2;enter_ind=0;Cursor.enb=1; Cursor.row=0;
		 Cursor.mode=1; Display.flag=1;Display.row=0; Cursor.size=0;
		 Display.suspend=1;SetDisplayPage(10);
	       }
	     }
	 } else ViewCursor(enter_ind);
       }
      } break;
    case 18: case 22:/*­ҐўҐа­л© Ї а®«м Ё«Ё § ЇаҐв*/
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) /*"ESC"*/
      {
	mmi_pass=0; Horizont=0; Display.flag=1; Display.write=0;
	enter_ind=0;
	if (flg_zero_meter==0 && flg_dyn_clr==0)
	  { Vertical=2; SetDisplayPage(16);} else
	{flg_zero_meter=flg_dyn_clr=0;Display.suspend=1;SetDisplayPage(10);}
      } break;
    case 20:/*бЇа ўЄ */
      if (MoveListMMI (buf_mmi,count,Display.size)==0)
      { 
        if (Display.flag==1) 
        {
          ClearBuffer();Vertical=Display.row+1;
          if ((Display.num+Display.row)<Display.size) 
	  {
	    j=strlen(conf_all[coord[0]]);
	    for (i=0;i<j;i++) mmi_str[i]=conf_all[coord[0]][i];
	    if (coord[1]<=40) ByteToString(coord[1]+1,j,1);
            Cursor.size++;
          } count_smb=27;Horizont=2;Display.evt=2;Display.row++;
          if (Display.row > 5)
          {
            Display.row=0;Display.flag=0;Cursor.mode=0;Cursor.old=Cursor.row;
            Cursor.row=0;Cursor.enb=1;Display.suspend=0;
          }
        } else MoveCursorMMI(buf_mmi,Cursor.size,count);
        if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
        { Display.num=0; ReturnToMenuMMI();} else
        if (KeyFound (buf_mmi,Key_0,Key_2,count)==1)
        {
	  Display.prm=Display.num+Cursor.row;mmi_pass=0;Display.flag=1;
	  Display.write=0;Horizont=0;enter_ind=0;Vertical=2; SaveOldPageMMI();
	  Display.old=Display.num; SetDisplayPage(16);
        }
      } break;
    case 21:/*Їа®б¬®ва ¤® 6 Їг­Єв®ў ўлЎ®а  §­ зҐ­Ёп*/
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
      {
	mmi_pass=Display.write=enter_ind=0;Horizont=0;Display.flag=1;
	Display.num=Display.old; Vertical=2; SetDisplayPage(16);
      } else/*"ESC"®в¬Ґ­  Ё§¬Ґ­Ґ­Ёп Ї а ¬Ґва */
      {
	MoveListMMI (buf_mmi,count,mmi_num_sel);
	ClearBuffer();Vertical=Display.row+1;
	if (Display.flag==1) /*б¬Ґ­  бЇЁбЄ */
	{ /*ўлў®¤ Їг­Єв  ¬Ґ­о ўлЎ®а §­ зҐ­Ёп §  ®¤Ё­ Їа®е®¤*/
	  if ((Display.num+Display.row)<mmi_num_sel)
	  {
	    j=strlen(name_sel_all[mmi_sel[Display.num+Display.row]]);
	    for (i=0;i<j;i++)
	    mmi_str[i+3]=name_sel_all[mmi_sel[Display.num+Display.row]][i];
	    Cursor.size++;
	  } count_smb=30; Horizont=0; Display.evt=2; Display.row++;
	  if (Display.row > 5)
	  {
	    Display.row=Display.flag=0;Cursor.mode=0;Cursor.old=Cursor.row;
	    Cursor.row=0;Cursor.enb=1;Display.suspend=0;
	  }
	} else MoveCursorMMI(buf_mmi,Cursor.size,count);
	if (KeyFound (buf_mmi,Key_0,Key_2,count)==1)
	{
	  cr[0]=Display.num+Cursor.row;mmi_pass=0;Horizont=0;Display.flag=1;
	  flg_init=ConfigParamChange(cr,1,coord[2]);enter_ind=0;
	  Vertical=2;SetDisplayPage(16);
	}
      } break;
    case 13:/*Їа®б¬®ва ¤® 6 Їг­Єв®ў ¬Ґ­о  ае в®зҐЄ*/
      if (MoveListMMI (buf_mmi,count,size_max)==0)
      {
        if (Display.flag==1) 
        {
          ClearBuffer();Vertical=Display.row+1;
          if ((Display.num+Display.row)<size_max)
	  { 
            if (coord[0]<Max_conf_all) for (i=0;i<5;i++)
	      mmi_str[i+2]=conf_all[coord[0]][i];
	      ByteToString(coord[1],8,0);
	      if (coord[2]<3) for (i=0;i<6;i++)
	      mmi_str[i+10]=name_arch[coord[2]][i];
	      if (coord[2]>0) mmi_str[16]=hex_to_ascii[coord[3]+1];
	      if (coord[2]>0)
	      {
		j=strlen(dyn_all[coord[4]]);
		if (coord[4]<Max_dynam_all) for (i=0;i<j;i++)
		mmi_str[i+17]=dyn_all[coord[4]][i];
		mmi_val[Display.row]=coord[6];k=strlen(name_mmi_exp[coord[5]]);
		if (coord[5]<Max_mmi_exp) if (coord[5]==4 || coord[5]==6)
		for (i=j;i<k+j;i++) if ((i+17)<30)
		mmi_str[i+17]=name_mmi_exp[coord[5]][i-j];
	      } else mmi_val[Display.row]=128; Cursor.size++;
	   } count_smb=30;Horizont=0;Display.evt=2;Display.row++;
          if (Display.row > 5) 
          {
            Display.row=Display.flag=0;Cursor.mode=0;Cursor.old=Cursor.row;
            Cursor.row=0;Cursor.enb=1;Display.suspend=0;
          }
        } else MoveCursorMMI(buf_mmi,Cursor.size,count);
        if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
        { Display.num=0; ReturnToMenuMMI();} else
        if (KeyFound (buf_mmi,Key_0,Key_2,count)==1 && mmi_val[Cursor.row]!=128)
        {
	  mmi_arc_page=GetArcPoint(&mmi_arc,&mmi_seg);Display.flag=1;
	  mmi_size=0;Display.prm=Display.num+Cursor.row;SetDisplayPage(19);
	}
      } break;
    case 19:
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1)
      {Display.flag=1;Display.row=0;Display.suspend=1;SetDisplayPage(13);} else
      { /*"C"«Ёбв вм  аеЁў ў­Ё§*/
	if (KeyFound (buf_mmi,Key_0,Key_7,count)==1 && mmi_size<2)
	{Display.row=0;Display.flag=1;} else
	{
	  if (mmi_arc<=0 && mmi_size<2) /*­ з «® б«Ґ¤гойҐЈ® Їа®е®¤ */
	  {mmi_size++;GetArcReadPoint(&mmi_arc,&mmi_seg,&mmi_arc_page);} else
	  M:if (Display.flag == 1)
	  {
	    ClearBuffer();Vertical=Display.row+1;
	    if (mmi_arc > 0)
	    {
	      mmi_arc--;mmi_adr=mmi_arc*Size_str;
	      if (FlashRead(mmi_seg,mmi_adr)==Display.point)
	      {
		k=0;for (i=0;i<3;i++)
		{ /*Їа®зЁв вм Ё Ї®Є § вм ¤ вг  аеЁў */
		  j=FlashRead(mmi_seg,mmi_adr+3-i);ByteToString(j,k,0);
		  if (i!=2) mmi_str[k+2]=Key_dot;k=k+3;
		} k=9;for (i=0;i<2;i++)
		{ /*Їа®зЁв вм Ё Ї®Є § вм ўаҐ¬п  аеЁў */
		  j=FlashRead(mmi_seg,mmi_adr+4+i);ByteToString(j,k,0);
		  if (i==0) mmi_str[k+2]=0x3a;k=k+3;
		} k=15;j=7+(Display.prm)*4;
		SecurityConvert(FlashRead(mmi_seg,mmi_adr+j),
		FlashRead(mmi_seg,mmi_adr+j+1),FlashRead(mmi_seg,mmi_adr+j+2),
		FlashRead(mmi_seg,mmi_adr+j+3),mmi_val);
		value=ConvToFloat(mmi_val[0],mmi_val[1],mmi_val[2],mmi_val[3]);
		FloatToString(value,mmi_str,k);
	      } else goto M;
	    } count_smb=24;Display.row++;Display.evt=2;
	    if (Display.row > 5) Display.flag=0;Horizont=0;
	  }
	}
      } break;
    case 25: /*гбв ­®ўЄ  ­г«п ¬ бб®¬Ґа */
      if (flg_zero_meter==3)
      {
	st_meter=dyn_prm;
	if ((st_meter & 131072)==0)
	{
	  Cursor.enb=1; Cursor.row=0; flg_zero_meter=0;
	  Cursor.mode=1; Display.flag=1;Display.row=0; Cursor.size=0;
	  Display.suspend=1; SetDisplayPage(10);
	}
      } break;
    case 26: /*ЇаҐ¤гЇаҐ¦¤Ґ­ЁҐ*/
      if (KeyFound(buf_mmi,Key_0,Key_6,count)==1) /*®вЄ § ®в Ё§¬Ґ­Ґ­Ёп*/
      {
	flg_zero_meter=0;flg_dyn_clr=0;Cursor.enb=1; Cursor.row=0;
	Cursor.mode=1; Display.flag=1;Display.row=0; Cursor.size=0;
	Display.suspend=1;SetDisplayPage(10);
      }
      if (KeyFound(buf_mmi,Key_0,Key_7,count)==1) /*Їа®¤®«¦Ґ­ЁҐ гбв ­г«п*/
      {
	flg_zero_meter=2; evt_meter[nmb_meter]=2; SetDisplayPage(25);
      }
    case 27: /*¬Ґ­о ўлЎ®а  ¬ бб®¬Ґа */
      if (Display.flag==1) WriteMenuToMMI(str_menu2[Display.num+Display.row],Max_pnt); else
      MoveCursorMMI(buf_mmi,Cursor.size,count);
      if (KeyFound (buf_mmi,Key_0,Key_6,count)==1) ReturnToMenuMMI(); else
      if (KeyFound (buf_mmi,Key_0,Key_2,count)==1)
      {
	nmb_meter=Cursor.row; Horizont=10; Vertical=3; ClearBuffer();
	flg_zero_meter=1; SetDisplayPage(17);
      } break;
    }
}
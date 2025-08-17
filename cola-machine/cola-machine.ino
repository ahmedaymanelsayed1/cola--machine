#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Stepper.h>

// تهيئة شاشة LCD (العنوان 0x27 قد يختلف، تحقق منه)
LiquidCrystal_I2C lcd(0x27, 20, 4);

// إعدادات الستيبر
const int STEPS_PER_REVOLUTION = 200; // عدد الخطوات لكل دورة
const int STEPS_PER_DRINK = 2450;     // عدد الخطوات لمسافة 7 سم (حسب النظام)
Stepper myStepper(STEPS_PER_REVOLUTION, 9, 8); // STEP على 9، DIR على 8

// دبابيس الريلاي
const int relayPins[] = {22, 23, 24, 25, 26, 27, 28}; // من 22 إلى 28
// دبابيس الأزرار
const int buttonPins[] = {30, 31, 32, 33, 34, 35, 36}; // من 30 إلى 36
// دبوس Enable للستيبر
const int ENABLE_PIN = 7;

// الموقع الحالي للستيبر (بالخطوات)
long currentPosition = 0;
// رقم المشروب الحالي (0 يعني الموقع الافتراضي)
int currentDrink = 0;

void setup() {
  // تهيئة الشاشة
  lcd.begin(20, 4);
  lcd.backlight();
  displayDrinks();

  // تهيئة دبابيس الريلاي
  for (int i = 0; i < 7; i++) {
    pinMode(relayPins[i], OUTPUT);
    if (i == 6) {
      digitalWrite(relayPins[i], LOW);  // ريلاي السابع يكون مبدأياً مطفأ (LOW = OFF)
    } else {
      digitalWrite(relayPins[i], HIGH); // بقية الريلايات (HIGH = OFF)
    }
  }

  // تهيئة دبابيس الأزرار
  for (int i = 0; i < 7; i++) {
    pinMode(buttonPins[i], INPUT);
  }

  // تهيئة دبوس Enable للستيبر
  pinMode(ENABLE_PIN, OUTPUT);
  digitalWrite(ENABLE_PIN, HIGH); // تعطيل الستيبر في البداية

  // إعداد سرعة الستيبر
  myStepper.setSpeed(100); // سرعة الستيبر (RPM)
}

void loop() {
  // التحقق من ضغط الأزرار
  for (int i = 0; i < 7; i++) {
    if (digitalRead(buttonPins[i]) == HIGH) {
      delay(50); // Debounce
      if (digitalRead(buttonPins[i]) == HIGH) {
        handleDrinkSelection(i + 1); // معالجة اختيار المشروب
        while (digitalRead(buttonPins[i]) == HIGH); // انتظار تحرير الزر
      }
    }
  }
}

// عرض قائمة المشروبات على الشاشة
void displayDrinks() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1:7UP 2:Pepsi 3:fanta");
  lcd.setCursor(0, 1);
  lcd.print("4:PINEAPPLE 5:LEMON");
  lcd.setCursor(0, 2);
  lcd.print("6:MANGO   7:TAMR");
  lcd.setCursor(0, 3);
  lcd.print("Select a drink...");
}

// معالجة اختيار المشروب
void handleDrinkSelection(int drink) {
  if (drink == currentDrink) return; // إذا كان المشروب هو الحالي، لا تفعل شيئًا

  // حساب المسافة المطلوبة (بالخطوات)
  long targetPosition = (drink - 1) * STEPS_PER_DRINK;
  long stepsToMove = targetPosition - currentPosition;

  // تفعيل الستيبر
  digitalWrite(ENABLE_PIN, LOW);

  // تحريك الستيبر
  myStepper.step(stepsToMove);

  // تعطيل الستيبر
  digitalWrite(ENABLE_PIN, HIGH);

  // تحديث الموقع الحالي
  currentPosition = targetPosition;
  currentDrink = drink;

  // تشغيل الريلاي لمدة 3 ثوانٍ حسب نوع الريلاي
  if (drink == 7) {
    digitalWrite(relayPins[drink - 1], HIGH); // تشغيل الريلاي السابع (HIGH = ON)
    delay(6000);
    digitalWrite(relayPins[drink - 1], LOW);  // إيقافه (LOW = OFF)
  } else {
    digitalWrite(relayPins[drink - 1], LOW);  // تشغيل بقية الريلايات (LOW = ON)
    delay(6000);
    digitalWrite(relayPins[drink - 1], HIGH); // إيقافها (HIGH = OFF)
  }

  // إعادة عرض الشاشة
  displayDrinks();
}

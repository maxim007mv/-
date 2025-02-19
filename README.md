# 🗺️ Система Оптимизации Туристических Маршрутов

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Build Status](https://github.com/your-username/route-optimizer/workflows/CI/badge.svg)](https://github.com/your-username/route-optimizer/actions)
[![Coverage](https://codecov.io/gh/your-username/route-optimizer/branch/main/graph/badge.svg)](https://codecov.io/gh/your-username/route-optimizer)

**Интеллектуальная система для планирования туристических маршрутов с учётом бюджета, времени и предпочтений**

<div align="center">
  <img src="docs/images/demo.png" alt="Demo Screenshot" width="80%">
  <p><em>Пример оптимизированного маршрута по Москве</em></p>
</div>

## ✨ Ключевые возможности

| 🎯 Функция | ⚡️ Возможности |
|------------|----------------|
| **Умная маршрутизация** | • Алгоритм Дейкстры для оптимальных путей<br>• Учёт пробок и загруженности<br>• Мультимодальные маршруты |
| **ИИ планирование** | • Генетические алгоритмы для расписания<br>• ML-прогнозирование времени посещения<br>• Адаптивные рекомендации |
| **Бюджетирование** | • Оптимизация затрат<br>• Учёт стоимости билетов<br>• Планирование питания |
| **Персонализация** | • Учёт интересов<br>• Темп путешествия<br>• Предпочтения по времени |

## 🎯 Пример использования

```cpp
#include "route_optimizer.hpp"

int main() {
    // Создаем оптимизатор с бюджетом 50000₽ на 3 дня
    RouteOptimizer optimizer(50000.0, 3, {"музеи", "рестораны"});
    
    // Генерируем маршрут по Москве
    auto plan = optimizer.generateOptimalRoute("Москва");
    
    // Получаем красиво отформатированный план
    std::cout << optimizer.formatTravelPlan(plan);
    
    return 0;
}
```

### 📋 Пример вывода

```
╔══════════════════════════════════════════════════╗
║           📝 План путешествия в Москву          ║
╚══════════════════════════════════════════════════╝

🗓️  Детальный план по дням:
┌──────────┬─────────────────────────┬──────────┬──────────┐
│   Время  │         Место          │ Длит-ть  │  Цена    │
├──────────┴─────────────────────────┴──────────┴──────────┤
│ День 1                                                    │
├──────────┬─────────────────────────┬──────────┬──────────┤
│ 09:00    │ Красная площадь        │ 2 часа   │    ₽0    │
│ 11:30    │ Третьяковская галерея  │ 3 часа   │  ₽500    │
...
```

## 🛠️ Установка

### Системные требования
- C++17 компилятор (GCC 11+ или Clang 14+)
- CMake 3.20+
- Boost 1.82.0+
- SQLite 3.x
- Node.js 18.x (для веб-интерфейса)

### Быстрая установка

```bash
# Клонируем репозиторий с подмодулями
git clone --recurse-submodules https://github.com/your-username/route-optimizer.git
cd route-optimizer

# Создаем и настраиваем конфигурацию
./setup_project.sh

# Собираем проект
cd build
make -j$(nproc)

# Запускаем тесты
ctest --output-on-failure
```

## 📚 Документация

Полная документация доступна в [Wiki](https://github.com/your-username/route-optimizer/wiki)

### Основные разделы:
- 🚀 [Руководство по началу работы](docs/getting-started.md)
- 📖 [API Reference](docs/api-reference.md)
- 🔧 [Конфигурация](docs/configuration.md)
- 🧪 [Примеры использования](docs/examples.md)

## 🤝 Вклад в проект

Мы приветствуем вклад в развитие проекта! Смотрите [CONTRIBUTING.md](CONTRIBUTING.md) для деталей.

## 📄 Лицензия

Copyright © 2024 Your Name

Распространяется под лицензией MIT. Смотрите [LICENSE](LICENSE) для деталей.

## 👥 Авторы

- **Ваше Имя** - *Создатель проекта* - [GitHub](https://github.com/username)

## 🙏 Благодарности

- [Boost](https://www.boost.org/) за C++ библиотеки
- [Leaflet](https://leafletjs.com/) за картографический движок
- Всем контрибьюторам проекта

## 📬 Контакты

- Email: your.email@example.com
- Telegram: [@username](https://t.me/username)
- Discord: [Сервер сообщества](https://discord.gg/example)

## 🌟 Особенности
| Категория       | Возможности                                                                 |
|-----------------|-----------------------------------------------------------------------------|
| 🚀 Оптимизация  | Алгоритмы Дейкстры и генетические методы                                    |
| 💡 Интеллект    | ML-модели для прогнозирования времени и стоимости                           |
| 📊 Аналитика    | Визуализация маршрутов и детализированные отчеты                            |
| 🔌 Интеграции (в течение недели)  | Поддержка Aviasales, Hotellook, РЖД API                                     |

## 🛠️ Технологический стек
### Бэкенд
![C++](https://img.shields.io/badge/C++17-00599C?logo=c%2B%2B&logoColor=white)
![Boost](https://img.shields.io/badge/Boost-1.82.0-%2300599C)
![SQLite](https://img.shields.io/badge/SQLite-07405E?logo=sqlite&logoColor=white)

### Фронтенд
![React](https://img.shields.io/badge/React-18.2-61DAFB?logo=react&logoColor=white)
![Leaflet](https://img.shields.io/badge/Leaflet-1.9.4-199900?logo=leaflet&logoColor=white)
![Webpack](https://img.shields.io/badge/Webpack-5.88.2-8DD6F9?logo=webpack&logoColor=black)

## 🚀 Быстрый старт
### Предварительные требования
- GCC 11+ или Clang 14+
- CMake 3.20+
- Node.js 18.x
- Python 3.10+ (для скриптов)

```bash
# Клонирование репозитория
git clone --recurse-submodules https://github.com/your-username/route-optimizer.git
cd route-optimizer

# Сборка бэкенда
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j$(nproc)

# Установка фронтенда
cd ../frontend
npm ci --production
npm run build
```

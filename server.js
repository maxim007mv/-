const express = require('express');
const cors = require('cors');
const axios = require('axios');
const app = express();

app.use(cors());
app.use(express.json());

const GEMINI_API_KEY = 'AIzaSyD8RbTSYv6h8OZ6wQalp2HPJhR0pjzH8NI';
const GEMINI_API_URL = 'https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent';

app.post('/generate-plan', async (req, res) => {
    const { country, startDate, endDate, format, goals, budget, additionalWishes } = req.body;
    
    // Формируем промпт для Gemini на русском языке
    const prompt = `Создай детальный план путешествия в формате markdown. Используй следующие параметры:

Основная информация:
* Страна: ${country}
* Даты поездки: с ${startDate} по ${endDate}
* Формат путешествия: ${format.join(', ')}
* Цели поездки: ${goals.join(', ')}
* Бюджет: ${budget} рублей
${additionalWishes ? `* Дополнительные пожелания: ${additionalWishes}` : ''}

Пожалуйста, структурируй план следующим образом:

# План путешествия в ${country}

## Краткое описание маршрута
[Краткое описание основных точек маршрута и общих впечатлений]

## Детальный план по дням
[Распиши каждый день с учетом формата путешествия и целей]

## Бюджет и расходы
* Авиабилеты/Транспорт: [примерная стоимость]
* Проживание: [варианты и цены]
* Питание: [средний чек, рекомендации]
* Развлечения и экскурсии: [стоимость основных активностей]
* Дополнительные расходы: [шоппинг, сувениры и т.д.]

## Рекомендации
* Где остановиться
* Местная кухня
* Транспорт
* Безопасность
* Местные особенности и традиции

## Полезная информация
* Важные фразы на местном языке
* Контакты экстренных служб
* Полезные приложения
* Советы по подготовке к поездке

Пожалуйста, учти следующие моменты:
1. Адаптируй план под указанный бюджет
2. Учитывай сезон поездки
3. Добавь местные секреты и неочевидные места
4. Укажи примерные цены в рублях
5. Добавь советы по экономии`;

    try {
        const response = await axios.post(
            `${GEMINI_API_URL}?key=${GEMINI_API_KEY}`,
            {
                contents: [{
                    parts: [{
                        text: prompt
                    }]
                }]
            }
        );

        const generatedPlan = response.data.candidates[0].content.parts[0].text;
        res.json({ plan: generatedPlan });
    } catch (error) {
        console.error('Ошибка при генерации плана:', error);
        res.status(500).json({ 
            error: 'Ошибка при генерации плана',
            details: error.message 
        });
    }
});

// Добавим тестовый маршрут
app.get('/test', (req, res) => {
    res.json({
        status: 'Сервер работает',
        message: 'API готов к использованию'
    });
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`Сервер запущен на порту ${PORT}`);
    console.log('Для проверки откройте: http://localhost:3000/test');
}); 
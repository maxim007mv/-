// Управление анимированной заставкой
document.addEventListener('DOMContentLoaded', function() {
    const intro = document.getElementById('intro');
    const mainContent = document.getElementById('mainContent');
    const startButton = document.getElementById('startButton');
    const form = document.getElementById('travelForm');

    // Обработчик кнопки "Начать путешествие"
    startButton.addEventListener('click', function() {
        intro.style.display = 'none';
        mainContent.style.display = 'flex';
    });

    // Функция возврата на главную
    window.returnToHome = function() {
        mainContent.style.display = 'none';
        intro.style.display = 'flex';
        // Сброс формы
        form.reset();
        // Сброс прогресс-бара и секций
        resetForm();
    }

    // Функция перехода к следующему шагу
    window.nextSection = function(step) {
        const sections = document.querySelectorAll('.form-section');
        sections.forEach(section => {
            section.classList.remove('active');
        });
        document.getElementById('section' + step).classList.add('active');
        
        updateProgressBar(step);
    }

    // Функция возврата к предыдущему шагу
    window.prevSection = function(step) {
        const sections = document.querySelectorAll('.form-section');
        sections.forEach(section => {
            section.classList.remove('active');
        });
        document.getElementById('section' + step).classList.add('active');
        
        updateProgressBar(step);
    }

    function updateProgressBar(step) {
        const progressSteps = document.querySelectorAll('.progress-step');
        progressSteps.forEach((stepEl, index) => {
            if (index < step) {
                stepEl.classList.add('active');
            } else {
                stepEl.classList.remove('active');
            }
        });
    }

    function resetForm() {
        // Показываем только первую секцию
        document.querySelectorAll('.form-section').forEach(section => {
            section.classList.remove('active');
        });
        document.getElementById('section1').classList.add('active');
        
        // Сбрасываем прогресс-бар
        document.querySelectorAll('.progress-step').forEach((step, index) => {
            if (index === 0) {
                step.classList.add('active');
            } else {
                step.classList.remove('active');
            }
        });
    }

    // Предотвращаем отправку формы (для демонстрации)
    form.addEventListener('submit', function(e) {
        e.preventDefault();
        alert('Форма отправлена!');
        returnToHome();
    });
});

// Добавляем анимацию для прогресс-бара
function updateProgressBar(sectionNumber) {
    const progressSteps = document.querySelectorAll('.progress-step');
    progressSteps.forEach((step, index) => {
        if (index < sectionNumber) {
            step.classList.add('active');
            step.style.animation = 'pulse 0.5s ease-out';
        } else {
            step.classList.remove('active');
            step.style.animation = '';
        }
    });
}

// Обновляем обработчик отправки формы
document.getElementById('travelForm').addEventListener('submit', async (e) => {
    e.preventDefault();
    
    const formData = new FormData(e.target);
    const data = {
        startDate: formData.get('startDate'),
        endDate: formData.get('endDate'),
        country: formData.get('country'),
        format: Array.from(formData.getAll('format')),
        goals: Array.from(formData.getAll('goals')),
        budget: formData.get('budget'),
        additionalWishes: formData.get('additionalWishes')
    };

    try {
        showLoadingOverlay();
        const response = await fetch('http://localhost:3000/generate-plan', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(data)
        });

        if (response.ok) {
            const result = await response.json();
            hideLoadingOverlay();
            showSuccessAnimation(result.plan, data);
        } else {
            throw new Error('Ошибка при генерации плана');
        }
    } catch (error) {
        console.error('Ошибка:', error);
        hideLoadingOverlay();
        showErrorMessage();
    }
});

function showLoadingOverlay() {
    const overlay = document.createElement('div');
    overlay.className = 'loading-overlay';
    overlay.innerHTML = `
        <div class="loading-content">
            <div class="loading-spinner"></div>
            <p>Генерируем ваш идеальный маршрут...</p>
        </div>
    `;
    document.body.appendChild(overlay);
}

function hideLoadingOverlay() {
    const overlay = document.querySelector('.loading-overlay');
    if (overlay) {
        overlay.remove();
    }
}

function formatPlanSection(title, content, icon) {
    return `
        <div class="plan-section ${title.toLowerCase()}">
            <h3><span class="section-icon">${icon}</span>${title}</h3>
            ${content}
        </div>
    `;
}

function showSuccessAnimation(planText, formData) {
    const successOverlay = document.createElement('div');
    successOverlay.className = 'success-overlay';
    
    // Разбираем markdown на секции
    const sections = planText.split('\n#').map(section => section.trim());
    let formattedSections = '';
    
    sections.forEach(section => {
        if (section.startsWith('# ')) section = section.slice(2);
        if (section.startsWith(' ')) section = section.slice(1);
        
        const lines = section.split('\n');
        const title = lines[0];
        const content = lines.slice(1).join('\n');
        
        let icon = '📝'; // Дефолтная иконка
        
        // Подбираем иконку в зависимости от заголовка
        if (title.includes('маршрут')) icon = '🗺️';
        if (title.includes('день') || title.includes('план')) icon = '📅';
        if (title.includes('бюджет')) icon = '💰';
        if (title.includes('рекомендации')) icon = '💡';
        if (title.includes('информация')) icon = 'ℹ️';
        
        const formattedContent = content
            .split('\n')
            .map(line => {
                if (line.startsWith('*')) {
                    return `<li>${line.replace('*', '').trim()}</li>`;
                } else if (line.match(/^\d+\./)) {
                    const [num, ...text] = line.split('.');
                    return `<li><div class="day-number">${num}</div><div>${text.join('.').trim()}</div></li>`;
                } else if (line.trim().length > 0) {
                    return `<p>${line}</p>`;
                }
                return '';
            })
            .join('');
        
        formattedSections += formatPlanSection(title, formattedContent, icon);
    });

    // Вычисляем количество дней
    const startDate = new Date(formData.startDate);
    const endDate = new Date(formData.endDate);
    const days = Math.ceil((endDate - startDate) / (1000 * 60 * 60 * 24));

    successOverlay.innerHTML = `
        <div class="success-content">
            <div class="plan-header">
                <div class="success-icon">✓</div>
                <h2>Ваш план путешествия готов!</h2>
            </div>
            
            <div class="quick-summary">
                <h3>Краткая сводка</h3>
                <div class="summary-grid">
                    <div class="summary-item">
                        <span class="icon">🗓️</span>
                        <span class="label">Длительность:</span>
                        <span class="value">${days} дней</span>
                    </div>
                    <div class="summary-item">
                        <span class="icon">💰</span>
                        <span class="label">Бюджет:</span>
                        <span class="value">${formData.budget} ₽</span>
                    </div>
                    <div class="summary-item">
                        <span class="icon">🎯</span>
                        <span class="label">Формат:</span>
                        <span class="value">${formData.format.join(', ')}</span>
                    </div>
                    <div class="summary-item">
                        <span class="icon">✨</span>
                        <span class="label">Цели:</span>
                        <span class="value">${formData.goals.join(', ')}</span>
                    </div>
                </div>
            </div>

            <div class="travel-plan">
                ${formattedSections}
            </div>
            
            <div class="button-group">
                <button onclick="downloadPlan()" class="download-button">
                    <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor">
                        <path d="M21 15v4a2 2 0 0 1-2 2H5a2 2 0 0 1-2-2v-4M7 10l5 5 5-5M12 15V3"/>
                    </svg>
                    Скачать план
                </button>
                <button onclick="closeOverlay()" class="close-button">Закрыть</button>
            </div>
        </div>
    `;
    document.body.appendChild(successOverlay);
}

function downloadPlan() {
    const planText = document.querySelector('.travel-plan').innerText;
    const blob = new Blob([planText], { type: 'text/plain' });
    const url = window.URL.createObjectURL(blob);
    const a = document.createElement('a');
    a.href = url;
    a.download = 'travel_plan.txt';
    a.click();
    window.URL.revokeObjectURL(url);
}

function closeOverlay() {
    const overlay = document.querySelector('.success-overlay');
    overlay.style.animation = 'fadeOut 0.5s ease-out forwards';
    setTimeout(() => overlay.remove(), 500);
}

function showErrorMessage() {
    const errorOverlay = document.createElement('div');
    errorOverlay.className = 'error-overlay';
    errorOverlay.innerHTML = `
        <div class="error-content">
            <div class="error-icon">✕</div>
            <h2>Произошла ошибка</h2>
            <p>К сожалению, не удалось сгенерировать план путешествия. Пожалуйста, попробуйте позже.</p>
            <button onclick="this.parentElement.parentElement.remove()" class="close-button">Закрыть</button>
        </div>
    `;
    document.body.appendChild(errorOverlay);
}

// Добавляем анимацию для полей ввода
document.querySelectorAll('.form-group input, .form-group textarea').forEach(input => {
    input.addEventListener('focus', () => {
        input.parentElement.style.transform = 'scale(1.02)';
    });
    
    input.addEventListener('blur', () => {
        input.parentElement.style.transform = 'scale(1)';
    });
}); 
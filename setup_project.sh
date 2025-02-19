#!/bin/bash

# Создаем корневую директорию проекта
mkdir -p travel_planner
cd travel_planner

# Создаем структуру директорий
echo "Создание структуры директорий..."
mkdir -p client/{public/{assets/images,src/{js,styles}},src}
mkdir -p server/src
mkdir -p core/{include/planner,src}

# Перемещаем файлы в соответствующие директории
echo "Перемещение файлов..."

# Клиентская часть
mv ../index.html client/public/
mv ../plane.svg client/public/assets/images/
mv ../styles.scss client/src/styles/
mv ../styles.css client/src/styles/
mv ../script.js client/src/js/

# Серверная часть
mv ../server.js server/src/

# C++ часть
mv ../main.cpp core/src/
mv ../travel_planner.hpp core/include/planner/TravelPlanner.hpp
mv ../route_optimizer.hpp core/include/planner/RouteOptimizer.hpp
mv ../route_graph.hpp core/include/planner/RouteGraph.hpp
mv ../schedule_optimizer.hpp core/include/planner/ScheduleOptimizer.hpp
mv ../visit_time_predictor.hpp core/include/planner/VisitTimePredictor.hpp
mv ../season_analyzer.hpp core/include/planner/SeasonAnalyzer.hpp
mv ../budget_manager.hpp core/include/planner/BudgetManager.hpp

# Копируем CMakeLists.txt в корневую директорию
mv ../CMakeLists.txt ./

# Создаем package.json для клиента
cat > client/package.json << 'EOF'
{
  "name": "travel-planner-client",
  "version": "1.0.0",
  "description": "Travel Planner Client Application",
  "main": "src/js/script.js",
  "scripts": {
    "start": "parcel public/index.html",
    "build": "parcel build public/index.html",
    "sass": "sass src/styles/styles.scss src/styles/styles.css --watch"
  },
  "dependencies": {
    "axios": "^0.21.1"
  },
  "devDependencies": {
    "parcel-bundler": "^1.12.5",
    "sass": "^1.32.8"
  }
}
EOF

# Создаем package.json для сервера
cat > server/package.json << 'EOF'
{
  "name": "travel-planner-server",
  "version": "1.0.0",
  "description": "Travel Planner Server Application",
  "main": "src/server.js",
  "scripts": {
    "start": "node src/server.js",
    "dev": "nodemon src/server.js"
  },
  "dependencies": {
    "express": "^4.17.1",
    "cors": "^2.8.5",
    "axios": "^0.21.1"
  },
  "devDependencies": {
    "nodemon": "^2.0.7"
  }
}
EOF

# Создаем скрипт сборки
cat > build.sh << 'EOF'
#!/bin/bash

# Сборка C++ части
mkdir -p build && cd build
cmake ..
make

# Установка зависимостей клиента
cd ../client
npm install

# Установка зависимостей сервера
cd ../server
npm install

# Запуск всех компонентов
echo "Запуск сервера..."
cd ../server && npm start &
echo "Запуск клиента..."
cd ../client && npm start &

# Ожидание завершения
wait
EOF

# Делаем скрипт сборки исполняемым
chmod +x build.sh

# Создаем .gitignore
cat > .gitignore << 'EOF'
# Dependencies
node_modules/
/client/node_modules
/server/node_modules

# Build
/build
/dist
/client/dist

# IDE
.idea/
.vscode/

# Misc
.DS_Store
.env
.env.local
.env.development.local
.env.test.local
.env.production.local

# Logs
npm-debug.log*
yarn-debug.log*
yarn-error.log*

# C++ build files
CMakeFiles/
CMakeCache.txt
*.o
*.so
*.dylib
EOF

# Инициализируем git репозиторий
git init

echo "Структура проекта успешно создана!"
echo "Для сборки и запуска проекта выполните: ./build.sh"

# Выводим структуру проекта
echo -e "\nСтруктура проекта:"
tree -L 4
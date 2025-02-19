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
//
//  main.swift
//  FirstCourseFirstTask
//
//  Copyright © 2017 E-Legion. All rights reserved.
//

// Импортируем необходимые модули
import Foundation
import FirstCourseFirstTaskChecker


let checker = Checker()


// Ваша задача создать экземпляр класса SimpleClass и структуры SimpleStruct.
// Эти объекты нужно передать в метод getKeyWordParts и вывести в консоль их свойства.
// Еще раз обращаем ваше внимание на то, что белый текст в серых прямоугольниках - это лишь
// плейсхолдеры. Вам нужно нажать на него и написать свой код.

let simpleClass = Checker.SimpleClass()
var simpleStruct = Checker.SimpleStruct()

checker.getKeyWordParts(simpleClass: simpleClass,
			            simpleStruct: &simpleStruct)

// Вывод в консоль. Вам достаточно передать в конструкцию "\()" свойство и оно будет добавлено в
// строку. Получившуюся строку передаем в функцию print() для вывода в консоль.
print("Первая часть кодового слова \(simpleClass.firstPart)")
print("Вторая часть кодового слова \(simpleStruct.secondPart)")


// Для получения следующей части кодового слова вам нужно реализовать функцию, принимающую
// на вход два целых числа в виде строки и возвращающую результат их сложения в виде Int.
// Для конвертации строки в число воспользуйтесь инициализатором Int("124")! Восклицательный знак
// используется только потому, что мы знаем, что Checker не будет передавать некорректную строку и
// преобразование в Int всегда завершится успешно. В реальных проектах такой код использовать не
// следует. Более подробная информация об Optionals представлена в одноименной лекции.

func firstFunction(lhs: String, rhs: String) -> Int {
    return Int(lhs)! + Int(rhs)!
}

// Передача функции на проверку
checker.checkFirstFunction(function: firstFunction)


// Для получения последней части кодового слова вам нужно реализовать еще одну функцию.
// Чтобы узнать требования к ней нажмите левой кнопкой мыши на метод checkSecondFunction с
// зажатой клавишей cmd. Для преобразования данных в строку можно воспользоваться инициализатором
// String(describing: 124). Эта инициализация всегда заканчивается успешно. Поэтому не нужно
// использовать восклицательный знак.


func secondFunction(_ currency: Checker.Currency, _ amount: Int) -> String {
    var sign: String = ""
    var value: Int = 0
    var negative: Bool = false
    
    switch currency {
    case .rub:
        sign = "₽"
    case .eur:
        sign = "€"
    case .usd:
        sign = "$"
    }
    
    negative = (amount < 0)
    value = (negative) ? -amount : amount
    
    if (negative) {
        return "(\(value)) \(sign)"
    }
    return "\(value) \(sign)"
}

// Передача второй функции на проверку
checker.checkSecondFunction(function: secondFunction)

//
//  main.swift
//  FirstCourseSecondTask
//
//  Copyright © 2017 E-Legion. All rights reserved.
//

import Foundation
import FirstCourseSecondTaskChecker


let checker = Checker()

checker.checkFirstFunction { (someNumbers) -> (Int, Int) in
    var evenCount: Int = 0
    var oddCount: Int = 0

    for number in someNumbers {
        if (number % 2 == 0) {
            evenCount += 1
        } else {
            oddCount += 1
        }
    }

    return (evenCount, oddCount)
}


checker.checkSecondFunction { (inputCircles) -> [Checker.Circle] in
    var circles = inputCircles

    circles.removeAll(where: { $0.color == .red })
    
    circles = circles.map { (inputCircle) -> Checker.Circle in
        var circle = inputCircle
        if (circle.color == .black) {
            circle.radius *= 2
        }
        if (circle.color == .green) {
            circle.color = .blue
        }
        return circle
    }
    
    circles.sort(by: { (left, right) -> Bool in
        if (left.color == .white && right.color != .white) {
            return true
        }
        if (right.color == .blue && left.color != .blue) {
            return true
        }
        return false
    })

    return circles
}


checker.checkThirdFunction { (workers) -> [Checker.Employee] in
    var employers = [Checker.Employee]()
    
    workers.forEach({ (worker) in
        if (worker.count == 3) {
            guard
                let fullName = worker["fullName"],
                let salary = worker["salary"],
                let company = worker["company"] else {
                    return
            }
            
            let employee = Checker.Employee(fullName: fullName, salary: salary, company: company)
            employers.append(employee)
        }
    })
    
    return employers
}


checker.checkFourthFunction { (names) -> [String : [String]] in
    var groupedNames = [String : [String]]()
    
    names.forEach({ (name) in
        guard let firstCharacter = name.first else {
            return
        }
        let key = String(firstCharacter)
        if groupedNames[key] != nil {
            groupedNames[key]!.append(name)
        } else {
            groupedNames[key] = [name]
        }
    })
    
    groupedNames = groupedNames.filter({$0.value.count >= 2})
    
    for key in groupedNames.keys {
        groupedNames[key]!.sort(by: {$0 > $1})
    }
    
    return groupedNames
}

// Этот файл пуст не по ошибке. В этот раз вам необходимо самостоятельно импортировать необходимые модули и запустить проверку

import Foundation
import FirstCourseThirdTaskChecker


let checker = Checker()

class Stack : ArrayInitializableStorage {
    var storage = Array<Int>()

    convenience required init(array: [Int]) {
       self.init()
        storage = array
    }
    
    override var count: Int {
        return self.storage.count
    }
    
    override func push(_ element: Int) {
        self.storage.append(element)
    }
    
    override func pop() -> Int {
        return storage.popLast()!
    }
}

class Queue: Stack {
    override func push(_ element: Int) {
        self.storage.insert(element, at: 0)
    }
}

checker.checkInheritance(stack: Stack(), queue: Queue())



struct Stack2 : StorageProtocol, ArrayInitializable  {
    var storage = Array<Int>()
    
    init() {}
    
    var count: Int {
        return storage.count
    }
    
    mutating func push(_ element: Int) {
        storage.append(element)
    }
    
    mutating func pop() -> Int {
        return storage.popLast()!
    }
    
    init(array: [Int]) {
        self.storage = array
    }
}

struct Queue2 : StorageProtocol, ArrayInitializable  {
    var storage = Array<Int>()
    
    init() {}
    
    var count: Int {
        return storage.count
    }
    
    mutating func push(_ element: Int) {
        self.storage.insert(element, at: 0)
    }
    
    mutating func pop() -> Int {
        return storage.popLast()!
    }
    
    init(array: [Int]) {
        self.storage = array.reversed()
    }
}



checker.checkProtocols(stack: Stack2(), queue: Queue2())



extension User : JSONSerializable, JSONInitializable {
    
    public func toJSON() -> String {
        return "{\"fullName\": \"\(self.fullName)\", \"email\": \"\(self.email)\"}"
    }
    
    public convenience init(JSON: String) {
        self.init()
        let parsed = try! JSONSerialization.jsonObject(with: JSON.data(using: .utf8)!) as! [String: String]
        
        self.fullName = parsed["fullName"]!
        self.email = parsed["email"]!
    }
    
    
}


checker.checkExtensions(userType: User.self)

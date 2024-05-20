

JSON（JavaScript Object Notation, JS对象简谱）是一种轻量级的数据交换格式。它采用完全独立于编程语言的文本格式来存储和表示数据。简洁和清晰的层次结构使得 JSON 成为理想的数据交换语言。 易于人阅读和编写，同时也易于机器解析和生成，并有效地提升网络传输效率。

## **基础语法**

JSON 语法是 JavaScript 对象表示语法的子集。json 对象中每个元素的都是以 `key : value` 的形式来组织的。通常 value 可以是对、数组、数字（整形或浮点）、布尔值、null。

一个 json 对象由 一对 `{}` 扩起来。一个 json 数组由 `[]` 扩起来，下面是一个 json 的数据：

```json
{
  "name": "John Doe",
  "age": 30,
  "isEmployed": true,
  "address": {
    "street": "123 Main St",
    "city": "Anytown",
    "state": "CA",
    "country": "USA"
  },
  "hobbies": ["reading", "traveling", "coding"],
  "friends": [
    {
      "name": "Jane Smith",
      "age": 28
    },
    {
      "name": "Tom Johnson",
      "age": 32
    }
  ]
}
```

这是一个描述一个人的JSON数据。下面是对其各个部分的解释：

1. **name**: 一个字符串，表示此人的名字，这里是"John Doe"。
2. **age**: 一个数字，表示此人的年龄，这里是30。
3. **isEmployed**: 一个布尔值，表示此人是否在职，这里是true。
4. **address**: 一个对象，包含此人的地址信息。

	* **street**: 街道地址，这里是"123 Main St"。
	* **city**: 城市名，这里是"Anytown"。
	* **state**: 州或省份名，这里是"CA"。
	* **country**: 国家名，这里是"USA"。

5. **hobbies**: 一个数组，包含此人的爱好。这里有三个爱好："reading", "traveling", "coding"。
6. **friends**: 一个数组，包含此人的朋友信息。每个朋友都是一个对象，包含他们的名字和年龄。

	* 第一个朋友的名字是"Jane Smith"，年龄是28。
	* 第二个朋友的名字是"Tom Johnson"，年龄是32。


## **序列化与反序列化**

JSON序列化和反序列化是数据处理中的两个重要概念，特别是在编程和网络通信中。它们分别用于将数据对象（如数组、对象等）转换为JSON格式的字符串，以及将JSON格式的字符串转换回数据对象。


在JSON序列化的过程中，数据对象的属性和值被转换成JSON格式的字符串表示。例如，一个JavaScript对象 `{ name: "John Doe", age: 30 }` 可能会被序列化为 JSON 字符串 `"{"name":"John Doe","age":30}"`。


在JSON反序列化的过程中，JSON字符串被解析并转换回原始的数据对象。例如，JSON 字符串 `"{"name":"John Doe","age":30}"` 可能会被反序列化为一个JavaScript对象 `{ name: "John Doe", age: 30 }`。


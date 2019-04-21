let f

// (param1, param2, ..., paramN) => { statements }
f = (a, b, c) => {
  console.log('a:', a)
  console.log('b:', b)
  console.log('c:', c)
  console.log()
}
f(10, 20, 30)

// (param1, param2, ..., paramN) => expression
//
// is equivalent to
//
// (param1, param2, ..., paramN) => { return expression }
f = (a, b, c) => { return a + b + c }
console.log(f(10, 20, 30)) // 60

f = (a, b, c) => a + b + c
console.log(f(10, 20, 30)) // 60

f = (a, b, c) => { a + b + c } // eslint-disable-line no-unused-expressions
console.log(f(10, 20, 30)) // undefined because return is missing
console.log()

// Parentheses are optional when there's only one parameter name.
//
// (singleParam) => { statements } is equivalent to
//
// is equivalent to
//
// singleParam => { statements }
f = (a) => { console.log(a) }
f(10)

f = a => { console.log(a) }
f(10)
console.log()

// Parentheses are necessary when there are no parameters.
f = () => { console.log(10) }
f()
console.log()

// Does not return an object literal. Braces begin function body.
//
// SyntaxError: Unexpected token :
// f = () => {'a': 'apple', 'b': 'ball'}

// Parenthesize the body of function to return an object literal
// expression.
f = () => ({ 'a': 'apple', 'b': 'ball' })
console.log(f())

// Of course, an explicit return statement also works.
f = () => { return { 'a': 'apple', 'b': 'ball' } }
console.log(f())
console.log()

// Rest parameters are supported.
f = (a, b, ...rest) => {
  console.log('a:', a)
  console.log('b:', b)
  console.log('rest:', rest)
}
f(10, 20, 30, 40)

f = (a, b, ...rest) => rest.length
console.log('rest.length:', f(10, 20, 30, 40)) // 2
console.log()

// Default parameters are supported.
f = (a, b, c = 1000, d = 2000) => {
  console.log('a:', a)
  console.log('b:', b)
  console.log('c:', c)
  console.log('d:', d)
}
f(10, 20, 30)

f = (a, b, c = 1000, d = 2000) => a + b + c + d
console.log('a + b + c + d:', f(10, 20, 30)) // 2060
console.log()

// Destructuring within the parameter list is also supported.
f = ([a, b] = [10, 20], { x: c } = { x: a + b }) => { console.log(a + b + c) }
f()
console.log() // 60

// Simplifying an anonymous function with arrow expressions.
let words = ['apple', 'ball', 'cat', 'dog']

console.log(words.map(function (word) {
  return word.length
}))

console.log(words.map((word) => { return word.length }))

console.log(words.map((word) => word.length))

console.log(words.map(word => word.length))

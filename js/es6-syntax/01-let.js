// Throws ReferenceError because x is not defined.
(function () {
  try {
    // ReferenceError
    console.log('x:', x) // eslint-disable-line no-undef
  } catch (e) {
    console.log(e.toString())
  }
})()
console.log()

// Does not throw ReferenceError because x is defined due to variable
// hoisting.
; (function () {
  // undefined
  console.log(x) // eslint-disable-line no-use-before-define
  var x = 10
})()
console.log()

// Throws ReferenceError because x is not defined. Variable hoisting
// does not occur with the let keyword.
; (function () {
  try {
    console.log(x) // eslint-disable-line no-use-before-define
  } catch (e) {
    console.log(e.toString())
  }

  let x = 10
  console.log('x:', x)
})()
console.log()

// Variables declared with let have block scope. They can be reassigned
// but cannot be redeclared in the same block.
; (function () {
  let x = 10
  console.log('block 0: x:', x) // 10

  { // eslint-disable-line no-lone-blocks
    console.log('block 1: x:', x) // 10
  }

  { // eslint-disable-line no-lone-blocks
    let x = 20
    console.log('block 2: x:', x) // 20
  }

  console.log('block 0: x:', x) // 10

  x = 30
  console.log('block 0: x:', x) // 30

  // SyntaxError: Identifier 'x' has already been declared
  // let x = 40
})()

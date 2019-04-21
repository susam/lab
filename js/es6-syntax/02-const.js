// Throws ReferenceError because x is not defined. Variable hoisting
// does not occur with the const keyword.
; (function () {
  try {
    console.log(x) // eslint-disable-line no-use-before-define
  } catch (e) {
    console.log(e.toString())
  }

  const x = 10
  console.log('x:', x)
})()
console.log()

// Variables declared with const cannot be redeclared or reassigned in
// the same block. A const with the same name can be declared in another
// block.
; (function () {
  const x = 10
  console.log('block 0: x:', x) // 10

  { // eslint-disable-line no-lone-blocks
    console.log('block 1: x:', x) // 10
  }

  {
    const x = 20
    console.log('block 2: x:', x) // 20
  }

  console.log('block 0: x:', x) // 10

  try {
    // TypeError: Assignment to constant variable.
    x = 30 // eslint-disable-line no-const-assign
  } catch (e) {
    console.log('e:', e.toString())
  }

  // SyntaxError: Identifier 'x' has already been declared
  // const x = 40
})()

// A const must be assigned a value.
; (function () {
  // SyntaxError: Missing initializer in const declaration
  // const x
})()

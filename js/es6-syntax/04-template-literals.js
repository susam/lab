// Template literals are string literals allowing embedded expressions.
// You can use multi-line strings and string interpolation features with
// them. They were called "template strings" in prior editions of the
// ES2015 specification.

// Template literals can contain placeholders. These are indicated by
// the dollar sign and curly braces (${expression}).

// Multi-line strings.
console.log(`line 1
  line 2
    line 3
`)

// Expression interpolation.
let a = 10
let b = 20
console.log(`a + b: ${a + b}`)
console.log()

// Nesting templates.
//
// We can nest a template literal within a placeholder.
console.log(`foo ${`bar`} ${`${`baz`}`}`)
console.log()

// Escaping.
console.log(`"foo"\n'bar'\n\`baz\``)

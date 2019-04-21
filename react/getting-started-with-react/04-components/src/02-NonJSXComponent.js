import React from 'react'

class NonJSXComponent extends React.Component {
  render() {
    return React.createElement(
      'div', { className: 'App' }, React.createElement(
        'h1', null, 'Hello, world from non-JSX component!'
      )
    )
  }
}

export default NonJSXComponent

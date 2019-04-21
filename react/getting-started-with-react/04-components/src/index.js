import React from 'react'
import ReactDOM from 'react-dom'
import JSXComponent from './01-JSXComponent'
import NonJSXComponent from './02-NonJSXComponent'
import Table from './03-Table'
import './index.css'

class Navigation extends React.Component {
  render() {
    return (
      <nav>
        <a href="#JSXComponent">01-JSXComponent</a>
        <a href="#NonJSXComponent">02-NonJSXComponent</a>
        <a href="#Table">03-Table</a>
        <hr />
      </nav>
    )
  }
}

function renderComponent(Component) {
  ReactDOM.render(<div><Navigation /><Component /></div>,
                  document.getElementById('root'))
}

let components = {
  JSXComponent: JSXComponent,
  NonJSXComponent: NonJSXComponent,
  Table: Table,
}

function renderApp() {
  let hash = window.location.hash
  if (hash === '') {
    renderComponent(JSXComponent)
  } else {
    renderComponent(components[hash.substring(1)])
  }
}

renderApp()

window.onhashchange = renderApp

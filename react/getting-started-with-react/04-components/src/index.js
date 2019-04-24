import React from 'react'
import ReactDOM from 'react-dom'
import JSXComponent from './01-JSXComponent'
import NonJSXComponent from './02-NonJSXComponent'
import ClassComponent from './03-ClassComponent'
import SimpleComponent from './04-SimpleComponent'
import NestedComponent from './05-NestedComponent'
import PropsComponent from './06-PropsComponent'
import './index.css'

class Navigation extends React.Component {
  render() {
    return (
      <nav>
        <a href="#JSXComponent">01-JSXComponent</a>
        <a href="#NonJSXComponent">02-NonJSXComponent</a>
        <a href="#ClassComponent">03-ClassComponent</a>
        <a href="#SimpleComponent">04-SimpleComponent</a>
        <a href="#NestedComponent">05-NestedComponent</a>
        <a href="#PropsComponent">06-PropsComponent</a>
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
  ClassComponent: ClassComponent,
  SimpleComponent: SimpleComponent,
  NestedComponent: NestedComponent,
  PropsComponent: PropsComponent,
}

function renderApp() {
  let hash = window.location.hash
  let key = hash === '' ? '' : hash.substring(1)
  let component = components[key]

  if (typeof component === 'undefined') {
    renderComponent(JSXComponent)
  } else {
    renderComponent(component)
  }
}

renderApp()

window.onhashchange = renderApp

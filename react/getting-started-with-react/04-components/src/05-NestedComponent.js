import React from 'react'

class ClassComponent extends React.Component {
  render() {
    return <h1>Class Component</h1>
  }
}

function SimpleComponent() {
  return <h1>Simple Component</h1>
}

class NestedClassComponent extends React.Component {
  render() {
    return (
      <div>
        <ClassComponent />
        <SimpleComponent />
      </div>
    )
  }
}

function NestedSimpleComponent() {
  return (
    <div>
      <ClassComponent />
      <SimpleComponent />
    </div>
  )
}

function NestedComponent() {
  return (
    <div>
      <NestedClassComponent />
      <NestedSimpleComponent />
    </div>
  )
}

export default NestedComponent

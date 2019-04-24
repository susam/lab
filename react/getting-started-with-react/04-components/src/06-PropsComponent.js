import React from 'react'

// Embedding JavaScript within tags.
class HeadingClassComponent extends React.Component {
  render() {
    const heading = 'X Class Component'
    return <h1>{heading.replace('X', 'Heading')}</h1>
  }
}

function HeadingSimpleComponent() {
  const heading = 'X Simple Component'
  return <h1>{`Heading ${heading.replace('X', '')}`}</h1>
}

class PropsHeadingClassComponent extends React.Component {
  render() {
    return <h1>{this.props.fooData}</h1>
  }
}

function PropsHeadingSimpleComponent(props) {
  return <h1>{props.fooData}</h1>
}

function TableComponent(props) {

  const rows = props.scrubsData.map((row, index) => {
    return (
      <tr key={index}>
        <td>{row.name}</td>
        <td>{row.role}</td>
      </tr>
    )
  })

  return (
    <div>
      <table>
        <thead>
          <tr>
            <th>{props.headingData.name}</th>
            <th>{props.headingData.role}</th>
          </tr>
        </thead>
        <tbody>
          {rows}
        </tbody>
      </table>
    </div>
  )
}

function PropsTableComponent() {
  const headings = {
    name: 'Name',
    role: 'Role',
  }

  const characters = [
    {
      name: 'John Dorian',
      role: 'Doctor',
    },
    {
      name: 'Christopher Turk',
      role: 'Surgeon',
    },
    {
      name: 'Carla Espinosa',
      role: 'Nurse',
    }
  ]
  return (
    <TableComponent headingData={headings} scrubsData={characters} />
  )
}


function PropsComponent() {
  const headingData = 'Props Heading Class Component'
  return (
    <div>
      <HeadingClassComponent />
      <HeadingSimpleComponent />
      <PropsHeadingClassComponent fooData="Props Heading Class Component" />
      <PropsHeadingClassComponent fooData={headingData} />
      <PropsHeadingSimpleComponent fooData="Props Heading Simple Component" />
      <PropsTableComponent />
    </div>
  )
}

export default PropsComponent

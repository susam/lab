import React from 'react'

function TableComponent(props) {
  const rows = props.scrubsData.map((row, index) => {
    return (
      <tr key={index}>
        <td>{row.name}</td>
        <td>{row.role}</td>
        <td>
          <button onClick={function () {props.removeCharacter(index)}}>Remove</button>
        </td>
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
            <th>Delete</th>
          </tr>
        </thead>
        <tbody>
          {rows}
        </tbody>
      </table>
    </div>
  )
}

class StateTableComponent extends React.Component {
  state = {
    characters: [
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
  }

  removeCharacter = index => {
    const characters = this.state.characters

    this.setState({
      characters: characters.filter(function (character, i) {
        return i !== index
      })
    })
  }

  render() {
    const headings = {
      name: 'Name',
      role: 'Role',
    }

    return (
      <TableComponent headingData={headings}
                      scrubsData={this.state.characters}
                      removeCharacter={this.removeCharacter} />
    )
  }
}

function StateComponent() {
  return (
    <div>
      <StateTableComponent />
    </div>
  )
}

export default StateComponent

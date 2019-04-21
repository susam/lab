import React from 'react'

class Table extends React.Component {
  render() {
    return (
      <table>
        <thead>
          <tr>
            <th>Name</th>
            <th>Location</th>
          </tr>
        </thead>
        <tbody>
          <tr>
            <td>Humpty Dumpty</td>
            <td>Wall</td>
          </tr>
          <tr>
            <td>Jerry Seinfield</td>
            <td>New York</td>
          </tr>
          <tr>
            <td>John Dorian</td>
            <td>California</td>
          </tr>
        </tbody>
      </table>
    )
  }
}

export default Table

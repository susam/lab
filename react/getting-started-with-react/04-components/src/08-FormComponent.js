import React from 'react'

class Form extends React.Component {
  constructor(props) {
    super(props)
    this.initialState = {
      name: '',
      job: '',
    }
    this.state = this.initialState
  }


  handleChange = event => {
    this.setState({
      [event.name]: event.value
    })
  }

  render() {
    return (
      <form>
        <label>Name</label>
        <input name="name" value="{this.state.name}"
               onChange={this.handleChange} />
        <label>Job</label>
        <input name="job" value="{this.state.job}"
               onChange={this.handleChange} />
      </form>
    )
  }
}

export default Form

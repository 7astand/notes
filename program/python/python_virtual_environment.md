# python virtual environment

[参考链接](https://stackoverflow.com/questions/41573587/what-is-the-difference-between-venv-pyvenv-pyenv-virtualenv-virtualenvwrappe)

- pyenv

 pyenv 会在 `~/.pyenv/` 目录下创建不同的 `python` 版本隔离
 `~/.pyenv/shims`
 `~/.pyenv/versions`

 安装指定版本的 python
 `pyenv install 3.12-dev`

 从指定版本(3.12-dev)创建(py312)虚拟环境
 `pyenv virtualenv 3.12-dev py312`

 全局激活虚拟环境
 `pyenv global py312`

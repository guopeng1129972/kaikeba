/* @flow */

import { toArray } from '../util/index'

export function initUse (Vue: GlobalAPI) {
  Vue.use = function (plugin: Function | Object) {
    const installedPlugins = (this._installedPlugins || (this._installedPlugins = []))
    if (installedPlugins.indexOf(plugin) > -1) {
      return this
    }
    // additional parameters
    // 1.比如 Vue.use(VueRouter,args,...)，截取VueRouter，把后面的转化为一个数组args
    const args = toArray(arguments, 1)
    // 2.组件在使用的时候，会传进来一个vue的构造函数_vue就是这里的this
    //3.比如function install(Vue,arg1,arg2)
    args.unshift(this)
    if (typeof plugin.install === 'function') {
      plugin.install.apply(plugin, args)
    } else if (typeof plugin === 'function') {
      plugin.apply(null, args)
    }
    installedPlugins.push(plugin)
    return this
  }
}

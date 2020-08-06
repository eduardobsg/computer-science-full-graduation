class PessoaTiposController < ApplicationController
  # GET /pessoa_tipos
  # GET /pessoa_tipos.xml
  def index
    @pessoa_tipos = PessoaTipo.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @pessoa_tipos }
    end
  end

  # GET /pessoa_tipos/1
  # GET /pessoa_tipos/1.xml
  def show
    @pessoa_tipo = PessoaTipo.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @pessoa_tipo }
    end
  end

  # GET /pessoa_tipos/new
  # GET /pessoa_tipos/new.xml
  def new
    @pessoa_tipo = PessoaTipo.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @pessoa_tipo }
    end
  end

  # GET /pessoa_tipos/1/edit
  def edit
    @pessoa_tipo = PessoaTipo.find(params[:id])
  end

  # POST /pessoa_tipos
  # POST /pessoa_tipos.xml
  def create
    @pessoa_tipo = PessoaTipo.new(params[:pessoa_tipo])

    respond_to do |format|
      if @pessoa_tipo.save
        format.html { redirect_to(@pessoa_tipo, :notice => 'Pessoa tipo was successfully created.') }
        format.xml  { render :xml => @pessoa_tipo, :status => :created, :location => @pessoa_tipo }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @pessoa_tipo.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /pessoa_tipos/1
  # PUT /pessoa_tipos/1.xml
  def update
    @pessoa_tipo = PessoaTipo.find(params[:id])

    respond_to do |format|
      if @pessoa_tipo.update_attributes(params[:pessoa_tipo])
        format.html { redirect_to(@pessoa_tipo, :notice => 'Pessoa tipo was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @pessoa_tipo.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /pessoa_tipos/1
  # DELETE /pessoa_tipos/1.xml
  def destroy
    @pessoa_tipo = PessoaTipo.find(params[:id])
    @pessoa_tipo.destroy

    respond_to do |format|
      format.html { redirect_to(pessoa_tipos_url) }
      format.xml  { head :ok }
    end
  end
end
